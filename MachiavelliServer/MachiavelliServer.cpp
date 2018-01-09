// MachiavelliServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Server.h"

using namespace std;


int main()
{
	try
	{
		Server server;
		server.init();
	}
	catch(...)
	{
		cout << "An unexpected error occurred!" << endl;
		cin.get();
	}

	return _CrtDumpMemoryLeaks();
}

