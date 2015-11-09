#include "net/packet.hpp"

mg::Packet::Packet() {
	m_flag = ENET_PACKET_FLAG_RELIABLE;
	m_size = 0;
}
mg::Packet::~Packet() {
	enet_packet_destroy(m_packet);
}

bool mg::Packet::setData(const void* data, size_t size) {
	if(m_packet != nullptr) {
		fprintf(stderr, "tried to set data for non-null packet.\n");	
		return false;
	}
	if(data == nullptr) {
		fprintf(stderr, "tried to set packet data to nullptr.\n");
		return false;
	}

	m_packet = enet_packet_create(data, size, m_flag);
	
	if(m_packet == nullptr) {
		fprintf(stderr, "failed to create enet packet.\n");
		return false;
	}

	m_size = size;

	return true;
}

size_t mg::Packet::getSize() const {
	return m_size;
}
