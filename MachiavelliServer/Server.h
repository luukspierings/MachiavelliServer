#pragma once

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <chrono>
using namespace std;

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Player.h"
#include "ClientInfo.h"
#include "CommandHandler.h"

class Server {

public:

	Server() {};

	void consume_command();
	void handle_client(Socket client);
	std::shared_ptr<ClientInfo> init_client_session(Socket client);

	void init();


private:

	bool running = true;

	Sync_queue<ClientCommand> queue;
	CommandHandler commandHandler;

	const int tcp_port{ 1080 };


};