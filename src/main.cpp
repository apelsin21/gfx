#include <enet/enet.h>
#include <cstdio>

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

	fprintf(stdout, "starting server at port %u.\n", server.getPort());

	while(true) {
		server.pollEvents(1000);
	}

	enet_deinitialize();

	return 0;
}
