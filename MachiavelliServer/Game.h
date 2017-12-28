#pragma once

#include <vector>
#include <memory>

#include "Building.h"
#include "Character.h"
#include "State.h"
#include "CharacterFactory.h"
#include "ClientInfo.h"

using namespace std;

class Game
{

public:

	Game() {
	
		characters = characterFactory.getCharacters();

	};
	~Game() {};

	void addClient(shared_ptr<ClientInfo> client);


	void nextCharacter();


	int getClientsAmount() const { return clients.size(); }

	void notifyAllPlayers(string message);

	void removeClient(ClientInfo& client);

private:

	CharacterFactory characterFactory;
	// buildingfactory
	
	vector<shared_ptr<ClientInfo>> clients;

	vector<unique_ptr<Building>> buildings;
	vector<unique_ptr<Character>> characters;

	unique_ptr<State> currentState;


};


