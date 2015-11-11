#ifndef PACKET_HPP
#define PACKET_HPP

#include <enet/enet.h>
#include <cstdio>
#include <cstring>

#include <vector>
#include <string>
#include <ostream>

namespace mg {
	class Packet {
		protected:
			ENetPacketFlag m_flag; //type of the packet, reliable, unreliable, etc.

			std::vector<char> m_data;
			void append(const void* data, std::size_t size);
		public:
			Packet(ENetPacketFlag = ENET_PACKET_FLAG_RELIABLE);
			~Packet();

			void clear();

			ENetPacket* getInternalPacket();

			size_t getSize() const;
			ENetPacketFlag getInternalPacketFlag() const;

			mg::Packet& operator >>(const std::string&);
			mg::Packet& operator >>(const char*);
			mg::Packet& operator >>(char);
			mg::Packet& operator >>(int);
			mg::Packet& operator >>(float);
			mg::Packet& operator >>(double);

			mg::Packet& operator <<(const std::string&);
			mg::Packet& operator <<(const char*);
			mg::Packet& operator <<(char);
			mg::Packet& operator <<(int);
			mg::Packet& operator <<(float);
			mg::Packet& operator <<(double);
	};
}

#endif //PACKET_HPP
