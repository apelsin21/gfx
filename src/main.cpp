#include <enet/enet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "net/packet.hpp"
#include "net/server.hpp"
#include "net/client.hpp"

int main(void) {
	if(enet_initialize() != 0) {
		printf("An error occurred while initializing ENet.\n");
		return -1;
	}

	mg::Server server;
	if(!server.initialize()) {
		return -1;
	}

	mg::Client client;
	if(!client.initialize()) {
		return -1;
	}

	mg::Packet packet;
	packet.setData("bajs", strlen("bajs") + 1);

	if(!client.connect("127.0.0.1", 1234)) {
		return -1;
	}

	while(true) {
		client.pollEvents(1);
		server.pollEvents(1);

		if(client.isConnected()) {
			client.send(packet);
		}
	}

	enet_deinitialize();

	return 0;
}
