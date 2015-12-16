#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <iostream>

#include <enet/enet.h>

#include "net/packet.hpp"
#include "net/server.hpp"
#include "net/client.hpp"

#include "game/game.hpp"

int main(void) {

	mg::Game game;

	if(!game.load()) {
		fprintf(stderr, "game failed to load.\n");
		return -1;
	}
	
	if(!game.run()) {
		fprintf(stderr, "game failed to run.\n");
		return -1;
	}

	return 0;

	////if(enet_initialize() != 0) {
	//	printf("An error occurred while initializing ENet.\n");
	//	return -1;
	//}

	//mg::Packet packet;
	//packet << "bajskorv";

	//mg::Server server;
	//if(!server.listen("", 1234)) {
	//	return -1;
	//}

	//mg::Client client;
	//client.connect("127.0.0.1", 1234);

	//bool run = true;
	//unsigned int rtt = 0;
	//unsigned int rttVariance = 0;

	//while(run) {
	//	if(rtt != client.getRTT()) {
	//		std::cout << "RTT: " << client.getRTT() << "\n";
	//	}
	//	if(rttVariance != client.getRTTVariance()) {
	//		std::cout << "Variance: " << client.getRTTVariance()<< "\n";
	//	}

	//	rtt = client.getRTT();
	//	rttVariance = client.getRTTVariance();

	//	auto onConnected = [&](){
	//		printf("client: connected.\n");
	//		client.disconnect();
	//	};
	//	auto onDisconnected = [&]() {
	//		printf("client: disconnected.\n");
	//		run = false;
	//	};
	//	auto onReceived = [&](const enet_uint8* data, std::size_t size) {
	//		printf("client: recieved data from server\n.");
	//	};
	//	client.consumeEvents(onConnected, onDisconnected, onReceived);

	//	server.pollEvents(0);
	//}

	//enet_deinitialize();
}
