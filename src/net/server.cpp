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

bool mg::Server::initialize() {
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
				&m_address.port);
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
					"Client connected from %s:%u.\n",
					m_addrString.get(),
					m_event.peer->address.port
				);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
        		printf(
					"A packet of length %u containing %s was received from %s on channel %u.\n",
                	m_event.packet->dataLength,
                	m_event.packet->data,
                	m_event.peer->data,
                	m_event.channelID
				);

				enet_packet_destroy(m_event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf(
					"%s disconnected.\n",
					m_event.peer->data
				);

				m_event.peer->data = NULL;
				break;
			default:
				printf("got unhandled event %i.\n", (int)m_event.type);
				break;
		}
	}
}
