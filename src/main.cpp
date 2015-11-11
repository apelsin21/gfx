#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <thread>
#include <mutex>
#include <iostream>

#include <enet/enet.h>

#include "net/packet.hpp"
#include "net/server.hpp"
#include "net/client.hpp"

int main(void) {
	if(enet_initialize() != 0) {
		printf("An error occurred while initializing ENet.\n");
		return -1;
	}
	std::string msg;

	mg::Packet packet;

	mg::Client client;
	client.initialize();

	client.connect("192.168.1.111", 1234);
	client.pollEvents(10);

	while(client.isConnected()) {
		std::cout << "type your message:\n";
		std::cin >> msg; 

		if(msg == "q" || msg == "quit") {
			break;
		} else {
			packet << msg;
			client.send(packet);
			packet.clear();
		}

		client.pollEvents(10);
	}

	client.disconnect();
	client.pollEvents(10);

	enet_deinitialize();

	return 0;
}
