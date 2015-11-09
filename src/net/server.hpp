#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

#include <enet/enet.h>

namespace mg {
	class Server {
		protected:
			ENetAddress _address;
			ENetEvent _event;
			ENetHost* _host;
		public:
			Server();
			~Server();

			bool initialize();

			unsigned short getPort() const;

			void pollEvents(unsigned int);
	};
}

#endif //SERVER_HPP
