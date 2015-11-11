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


	mg::Packet packet;
	mg::Client client;
	client.connect("192.168.1.111", 1234);

	bool connected = false;
	while(!connected) {
		auto onConnected = [&]() {
			printf("connected.\n");
			connected = true;
		};
		auto onDisconnected = [&]() {};
		auto onReceived = [&](const enet_uint8* data, std::size_t size) {};
		client.consumeEvents(onConnected, onDisconnected, onReceived);
	}

	while(connected) {
		std::string msg;
		std::cout << "send a message: ";
		std::cin >> msg;

		if(msg == "q" || msg == "quit") {
			client.disconnect();
			break;
		} else {
			packet.clear();
			packet << msg;
			client.send(packet);
		}

		auto onConnected = [&](){};
		auto onDisconnected = [&]() {
			printf("disconnected.\n");
			connected = false;
		};
		auto onReceived = [&](const enet_uint8* data, std::size_t size) {
			printf("recieved data from server\n.");
		};
		client.consumeEvents(onConnected, onDisconnected, onReceived);
	}

	enet_deinitialize();

	return 0;
}
