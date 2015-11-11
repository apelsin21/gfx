#include "net/client.hpp"

mg::Client::Client() {
	m_isConnected = false;
	m_shouldExitThread = false;
}
mg::Client::~Client() {
}
void mg::Client::runInThread(const ENetAddress& address) {
	ENetHost* host = enet_host_create(nullptr, 1, 2, 0, 0);
	if(host == nullptr) {
		printf("failed to create ENet client host.\n");
		return;
	}

	ENetPeer* peer = enet_host_connect(host, &address, 2, 0);
	if(peer == nullptr) {
		printf("enet_host_connect failed.\n");
		return;
	}

	unsigned int timeout = 3000;
	enet_peer_timeout(peer, 0, timeout, timeout);

	bool isDisconnecting = false;
	unsigned int disconnectStartTime = 0;

	while(peer != nullptr) {
		m_roundTrip = peer->roundTripTime;
		m_roundTripVariance = peer->roundTripTimeVariance;
		
		if(m_shouldExitThread) {
			if(!isDisconnecting) {
				enet_peer_disconnect(peer, 0);
				isDisconnecting = true;
				disconnectStartTime = enet_time_get();
			} else {
				if((enet_time_get() - disconnectStartTime) > timeout) {
					printf("forcing disconnect, timeout %u reached.\n", timeout);
					enet_peer_reset(peer);
					peer = nullptr;
					break;
				}
			}
		}

		if(!isDisconnecting) {
			sendQueuedPacketsInThread(peer);
		}

		enet_host_service(host, 0, 0);

		{
			ENetEvent e;
			while(enet_host_check_events(host, &e) > 0) {
				std::lock_guard<std::mutex> lock(m_eventQueueMutex);
				m_eventQueue.push(e);
				if(e.type == ENET_EVENT_TYPE_DISCONNECT) {
					peer = nullptr;
					break;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	enet_host_destroy(host);
}
void mg::Client::sendQueuedPacketsInThread(ENetPeer* peer) {
	if(peer != nullptr && !m_packetQueue.empty()) {
		std::lock_guard<std::mutex> lock(m_packetQueueMutex);
		while(!m_packetQueue.empty()) {
			auto qp = m_packetQueue.front();
			m_packetQueue.pop();

			if(enet_peer_send(peer, 0, qp) != 0) {
				printf("client failed to send packet.\n");
			}
			if(qp->referenceCount == 0) {
				enet_packet_destroy(qp);
			}
		}
	}
}

void mg::Client::connect(const std::string& ip, unsigned short port) {
	if(ip.empty()) {
		fprintf(stderr, "tried to connect client to an empty address.\n");
		return;
	}

	ENetAddress connectionAddress;
	
	enet_address_set_host(&connectionAddress, ip.c_str());
	connectionAddress.port = port;

	m_shouldExitThread = false;
	m_workerThread = std::make_unique<std::thread>(&mg::Client::runInThread, this, connectionAddress);
}
void mg::Client::disconnect() {
	if(m_workerThread != nullptr) {
		m_shouldExitThread = true;
		m_workerThread->join();
		m_workerThread.release();
	}

	destroyPacketQueue();
	destroyEventQueue();
}
void mg::Client::consumeEvents(
		std::function<void()> onConnected,
		std::function<void()> onDisconnected,
		std::function<void(const enet_uint8* data, std::size_t size)> onReceived) {

	while(!m_eventQueue.empty()) {
		{
			std::lock_guard<std::mutex> lock(m_eventQueueMutex);
			m_eventQueueCopy = m_eventQueue;
			m_eventQueue = std::queue<ENetEvent> {};
		}

		bool isDisconnected = false;

		while(!m_eventQueueCopy.empty()) {
			auto& e = m_eventQueueCopy.front();

			switch(e.type) {
				case ENET_EVENT_TYPE_CONNECT:
					onConnected();
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					onDisconnected();
					isDisconnected = true;
					break;
				case ENET_EVENT_TYPE_RECEIVE:
					onReceived(e.packet->data, e.packet->dataLength);
					enet_packet_destroy(e.packet);
					break;
				case ENET_EVENT_TYPE_NONE:
					break;
				default:
					break;
			}
			m_eventQueueCopy.pop();
		}

		if(isDisconnected) {
			disconnect();
		}
	}
}

void mg::Client::send(mg::Packet& packet) {
	if(m_workerThread != nullptr) {
		std::lock_guard<std::mutex> lock(m_packetQueueMutex);
		auto enetPacket = packet.getInternalPacket();
		m_packetQueue.emplace(enetPacket);
	}
}

void mg::Client::destroyPacketQueue() {
	std::lock_guard<std::mutex> lock(m_packetQueueMutex);
	while(!m_packetQueue.empty()) {
		enet_packet_destroy(m_packetQueue.front());
		m_packetQueue.pop();
	}
}

void mg::Client::destroyEventQueue() {
	std::lock_guard<std::mutex> lock2(m_eventQueueMutex);
	while(!m_eventQueue.empty()) {
		auto& e = m_eventQueue.front();
		if(e.type == ENET_EVENT_TYPE_RECEIVE) {
			enet_packet_destroy(e.packet);
		}
		m_eventQueue.pop();
	}
}
