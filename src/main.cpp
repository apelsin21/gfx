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

	mg::Client client;
	if(!client.initialize()) {
		return -1;
	}

	mg::Packet packet;
	packet.setData("nä!", strlen("") + 1);

	if(!client.connect("192.168.1.3", 1234)) {
		return -1;
	}

	client.pollEvents(10);

	client.send(packet);

	while(client.isConnected()) {
		client.pollEvents(100);
	}

	enet_deinitialize();

	return 0;
}
