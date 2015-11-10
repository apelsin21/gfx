#include "net/client.hpp"

mg::Client::Client() {
	m_isConnected = false;
	m_host = nullptr;
	m_peer = nullptr;
}
mg::Client::~Client() {
	if(m_peer != nullptr) {
		enet_peer_reset(m_peer);
	}
	if(m_host != nullptr) {
		enet_host_destroy(m_host);
	}
}

bool mg::Client::initialize() {
	if(m_host != nullptr) {
		fprintf(stderr, "tried to re-initialize client.\n");
		return false;
	}

	m_host = enet_host_create(NULL, 1, 2, 0, 0);
	if(m_host == nullptr) {
		fprintf(stderr, "failed to create ENet host.\n");
		return false;
	}

	return true;
}

bool mg::Client::connect(const std::string& ip, unsigned short port) {
	if(m_host == nullptr) {
		fprintf(stderr, "failed to connect uninitialized client to ipaddr %s:%u.\n",
				ip.c_str(),
				port
		);
		m_isConnected = false;
		return false;
	}
	if(ip.empty()) {
		fprintf(stderr, "tried to connect client to and empty address.\n");
		m_isConnected = false;
		return false;
	}

	enet_address_set_host(&m_connectionAddress, ip.c_str());
	m_connectionAddress.port = port;

	m_peer = enet_host_connect(m_host, &m_connectionAddress, 2, 0);

	if(m_peer == nullptr) {
		fprintf(stderr, "failed to connect to peer at ipaddr %s:%u.\n", ip.c_str(), port);
		m_isConnected = false;
		return false;
	}

	return true;
}
bool mg::Client::disconnect() {
	if(m_host == nullptr) {
		fprintf(stderr, "tried to disconnect an uninitialized client.\n");
		return false;
	}
	if(m_peer == nullptr || !m_isConnected) {
		fprintf(stderr, "tried to disconnect an unconnected client.\n");
		return false;
	}

	enet_peer_disconnect(m_peer, 0);
	
	return false;
}
bool mg::Client::forceDisconnect() {
	if(m_host == nullptr) {
		fprintf(stderr, "tried to disconnect an uninitialized client.\n");
		return false;
	}
	if(m_peer == nullptr || !m_isConnected) {
		fprintf(stderr, "tried to disconnect an unconnected client.\n");
		return false;
	}

	enet_peer_reset(m_peer);

	m_isConnected = false;
	return true;
}

void mg::Client::pollEvents(unsigned int timeout) {
	if(m_host == nullptr) {
		fprintf(stderr, "tried to poll events for uninitialized client.\n");
		return;
	}

	while(enet_host_service(m_host, &m_event, timeout) > 0) {
		switch(m_event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("connected to server.\n");
				m_isConnected = true;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
        		printf(
					"A packet of length %u containing %s was received from %s on channel %u.\n",
                	m_event.packet->dataLength,
                	m_event.packet->data,
                	m_event.peer->data,
                	m_event.channelID
				);

				enet_packet_destroy(m_event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("disconnected from server.\n");

				m_event.peer->data = NULL;
				m_isConnected = false;
				break;
			default:
				printf("got unhandled event type %i.\n", (int)m_event.type);
				break;
		}
	}
}

bool mg::Client::send(mg::Packet& packet) {
	if(m_host == nullptr) {
		fprintf(stderr, "tried to send packet from uninitialized client.\n");
		return false;
	}
	if(m_peer == nullptr) {
		fprintf(stderr, "tried to send packet from unconnected client.\n");
		return false;
	}

	if(packet.getInternalPacket() == nullptr) {
		printf("client tried to send packet with no data.\n");
		return false;
	}

	enet_peer_send(m_peer, 0, packet.getInternalPacket());

	return true;
}

bool mg::Client::isConnected() const {
	return m_isConnected;
}
