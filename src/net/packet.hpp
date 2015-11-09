#ifndef PACKET_HPP
#define PACKET_HPP

#include <enet/enet.h>
#include <cstdio>

namespace mg {
	class Packet {
		protected:
			ENetPacket* m_packet;
			ENetPacketFlag m_flag; //type of the packet, reliable, unreliable, etc.
			unsigned int m_size; //content size in bytes
		public:
			Packet();
			~Packet();

			bool setData(const void*, size_t);

			size_t getSize() const;
	};
}

#endif //PACKET_HPP
