#pragma once

#include "Game.h"
#include "Player.h"
#include "Socket.h"

#include <string>
#include <memory>

using namespace std;


class CommandHandler
{
public:

	void handle(shared_ptr<ClientInfo> client, string command);
	const string getPrompt();
	void prompt(Socket& client);


private:

	Game game;

	const string promptText{ "machiavelli> " };



	

};




