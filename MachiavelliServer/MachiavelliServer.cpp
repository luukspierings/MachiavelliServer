// MachiavelliServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Server.h"

using namespace std;


int main()
{

	Server* server = new Server();
	server->init();
	delete server;

	return _CrtDumpMemoryLeaks();
}

