#include "net/packet.hpp"

mg::Packet::Packet(ENetPacketFlag flag) {
	m_flag = flag;
}
mg::Packet::~Packet() {
}

void mg::Packet::clear() {
	m_data.clear();
}

void mg::Packet::append(const void* data, std::size_t size) {
	if((size > 0)) {
		std::size_t start = m_data.size();
		m_data.resize(start + size);
		std::memcpy(&m_data[start], data, size);
	}
}

mg::Packet& mg::Packet::operator <<(const std::string& data) {
	if(data.empty()) {
		return *this;
	}

	append((void*)data.c_str(), data.size());

	return *this;
}
mg::Packet& mg::Packet::operator <<(const char* data) {
	if(data == nullptr) {
		return *this;
	}

	std::size_t length = static_cast<std::size_t>(std::strlen(data));
	append((void*)data, length);

	return *this;
}
mg::Packet& mg::Packet::operator <<(int data) {
	append((void*)&data, sizeof(data));

	return *this;
}
mg::Packet& mg::Packet::operator <<(float data) {
	append((void*)&data, sizeof(data));

	return *this;
}
mg::Packet& mg::Packet::operator <<(double data) {
	append((void*)&data, sizeof(data));

	return *this;
}

ENetPacket* mg::Packet::getInternalPacket() {
	ENetPacket* packet = enet_packet_create((void*)&m_data[0], m_data.size() + 1, m_flag);
	return packet;
}

ENetPacketFlag mg::Packet::getInternalPacketFlag() const {
	return m_flag;
}
size_t mg::Packet::getSize() const {
	return m_data.size();
}
