#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdio>

#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <memory>

#include <enet/enet.h>

#include "net/packet.hpp"

namespace mg {
	class Client {
		protected:
			bool m_isConnected, m_shouldExitThread;
			std::mutex m_eventQueueMutex, m_packetQueueMutex;
			std::queue<ENetEvent> m_eventQueue, m_eventQueueCopy;
			std::queue<ENetPacket*> m_packetQueue;
			std::unique_ptr<std::thread> m_workerThread;

			long m_roundTrip, m_roundTripVariance; //in milliseconds

			void runInThread(const ENetAddress&);
			void sendQueuedPacketsInThread(ENetPeer*);
			void destroyEventQueue();
			void destroyPacketQueue();
		public:
			Client();
			~Client();

			bool isConnected() const;

			void connect(const std::string&, unsigned short);
			void disconnect();

			void send(mg::Packet&);

			void consumeEvents(
				std::function<void()>,
				std::function<void()>,
		   		std::function<void(const enet_uint8*, std::size_t)>
			);
	};
}

#endif //CLIENT_HPP
