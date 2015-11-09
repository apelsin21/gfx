#include "net/server.hpp"

mg::Server::Server() {
	_address.host = ENET_HOST_ANY;
	_address.port = 1234;
}
mg::Server::~Server() {
	if(_host != nullptr) {
		enet_host_destroy(_host);
	}
}

bool mg::Server::initialize() {
	_host = enet_host_create(
		&_address,
		32,
		2,
		0, 
		0
	);

	if(_host == nullptr) {
		printf("An error occurred while trying to create an ENet server host.\n");
		return false;
	}

	return true;
}
unsigned short mg::Server::getPort() const {
	return _address.port;
}

void mg::Server::pollEvents(unsigned int timeout) {
	while(enet_host_service(_host, &_event, timeout) > 0) {
		switch(_event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf(
					"a new client from %x:%u.\n",
					_event.peer->address.host,
					_event.peer->address.port
				);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
        		printf(
					"A packet of length %u containing %s was received from %s on channel %u.\n",
                	_event.packet->dataLength,
                	_event.packet->data,
                	_event.peer->data,
                	_event.channelID
				);

				enet_packet_destroy(_event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf(
					"%s disconnected.\n",
					_event.peer->data
				);

				_event.peer->data = NULL;
				break;
			default:
				printf("got unhandled event %i.\n", (int)_event.type);
				break;
		}
	}
}
