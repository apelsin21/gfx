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

			std::string _hostString;
		public:
			Server();
			~Server();

			bool initialize();

			void setAddress(const std::string&, unsigned short);
			std::string getAddress() const;

			void pollEvents(unsigned int);
	};
}

#endif //SERVER_HPP
