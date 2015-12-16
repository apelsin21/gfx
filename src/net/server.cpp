#include "net/server.hpp"

mg::Server::Server() {
	m_address.host = ENET_HOST_ANY;
	m_address.port = 1234;

	m_maxAddrStringSize = 64;
	m_addrString = std::make_unique<char[]>(m_maxAddrStringSize);
}
mg::Server::~Server() {
	if(m_host != nullptr) {
		enet_host_destroy(m_host);
	}
}

bool mg::Server::listen(const std::string& ip, unsigned short port) {
	enet_address_set_host(&m_address, ip.c_str());
	m_address.port = port;

	m_host = enet_host_create(
		&m_address,
		32,
		2,
		0, 
		0
	);

	if(m_host == nullptr) {
		printf("An error occurred while trying to create an ENet server host.\n \
				Most likely, the port %u is already bound and therefore unavailable.\n",
				m_address.port);
		return false;
	}

	return true;
}
std::string mg::Server::getAddress() {
	if(enet_address_get_host_ip(&m_address, m_addrString.get(), m_maxAddrStringSize) < 0) {
		fprintf(stderr, "failed to get address string for server.\n");
		return "";
	}

	return std::string(m_addrString.get());
}

unsigned short mg::Server::getPort() const {
	return m_address.port;
}

void mg::Server::pollEvents(unsigned int timeout) {
	while(enet_host_service(m_host, &m_event, timeout) > 0) {
		switch(m_event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				if(enet_address_get_host_ip(&m_event.peer->address, m_addrString.get(), m_maxAddrStringSize) < 0) {
					fprintf(stderr, "failed to get address string for connecting client address.\n");
				}

				printf(
					"%s:%u connected.\n",
					m_addrString.get(),
					m_event.peer->address.port
				);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				if(enet_address_get_host_ip(&m_event.peer->address, m_addrString.get(), m_maxAddrStringSize) < 0) {
					fprintf(stderr, "failed to get address string for disconnecting client address.\n");
				}
        		printf(
					"%s:%u : %s.\n",
					m_addrString.get(),
					m_event.peer->address.port,
                	m_event.packet->data
				);

				enet_packet_destroy(m_event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				if(enet_address_get_host_ip(&m_event.peer->address, m_addrString.get(), m_maxAddrStringSize) < 0) {
					fprintf(stderr, "failed to get address string for disconnecting client address.\n");
				}

				printf(
					"%s:%u disconnected.\n",
					m_addrString.get(),
					m_event.peer->address.port
				);

				m_event.peer->data = NULL;
				break;
			default:
				printf("got unhandled event %i.\n", (int)m_event.type);
				break;
		}
	}
}
