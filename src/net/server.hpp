#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <memory>

#include <enet/enet.h>

namespace mg {
	class Server {
		protected:
			ENetAddress m_address;
			ENetEvent m_event;
			ENetHost* m_host;

			std::unique_ptr<char[]> m_addrString;
			size_t m_maxAddrStringSize;
		public:
			Server();
			~Server();

			bool initialize();

			std::string getAddress();
			unsigned short getPort() const;

			void pollEvents(unsigned int);
	};
}

#endif //SERVER_HPP
