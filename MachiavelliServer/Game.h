#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <random>

#include "Building.h"
#include "Character.h"
#include "State.h"
#include "CharacterFactory.h"
#include "BuildingFactory.h"
#include "ClientInfo.h"
#include "RandomGenerator.h"

#include "ChooseCharacter.h"

using namespace std;

class Game
{

public:

	Game() {
	
		characters = characterFactory.getCharacters();
		setCharacterOrder();

		buildings = buildingFactory.getBuildings();
		shuffleBuildings();

	};
	~Game() {};

	void addClient(shared_ptr<ClientInfo> client);
	void removeClient(ClientInfo& client);
	int getClientsAmount() const { return static_cast<int>(clients.size()); }

	Player& otherPlayer(Player& player);

	void setCharacterOrder();
	void shuffleBuildings();

	auto charactersBegin() { return characters.begin(); }
	auto charactersEnd() { return characters.end(); }
	void removeCharacter(vector<unique_ptr<Character>>::iterator it) { characters.erase(it); }

	bool hasState() { return (!!currentState); };
	State& getCurrentState() { return *currentState; };

	void start();

	void callNextCharacter(string lastCharacter = "");


	void notifyAllPlayers(string message);


private:

	CharacterFactory characterFactory;
	BuildingFactory buildingFactory;

	vector<unique_ptr<Building>> buildings;
	vector<unique_ptr<Character>> characters;
	vector<string> characterOrder;

	unique_ptr<State> currentState;


	vector<shared_ptr<ClientInfo>> clients;

};


