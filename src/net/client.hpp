#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdio>

#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <memory>
#include <atomic>

#include <enet/enet.h>

#include "net/packet.hpp"

namespace mg {
	class Client {
		protected:
			std::mutex m_eventQueueMutex, m_packetQueueMutex;
			std::queue<ENetEvent> m_eventQueue, m_eventQueueCopy;
			std::queue<ENetPacket*> m_packetQueue;
			std::unique_ptr<std::thread> m_workerThread;

			std::atomic_bool m_shouldExitThread;
			std::atomic_uint_fast32_t m_rtt, m_rttVariance; //in milliseconds

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

			unsigned int getRTT() const;
			unsigned int getRTTVariance() const;

			void consumeEvents(
				std::function<void()>,
				std::function<void()>,
		   		std::function<void(const enet_uint8*, std::size_t)>
			);
	};
}

#endif //CLIENT_HPP
