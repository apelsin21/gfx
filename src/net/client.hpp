#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

#include <cstdio>

#include <enet/enet.h>

#include "net/packet.hpp"

namespace mg {
	class Client {
		protected:
			ENetHost* m_host;
			ENetPeer* m_peer;
			ENetEvent m_event;
			ENetAddress m_connectionAddress;

			bool m_isConnected;
		public:
			Client();
			~Client();

			bool initialize();

			bool connect(const std::string&, unsigned short);
			bool disconnect();
			bool forceDisconnect();

			bool send(mg::Packet&);

			void pollEvents(unsigned int);

			bool isConnected() const;
	};
}

#endif //CLIENT_HPP
