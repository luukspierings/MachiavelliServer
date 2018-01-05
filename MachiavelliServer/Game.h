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
		resetCharacters();

		buildings = buildingFactory.getBuildings();
		shuffleBuildings();
	};

	void addClient(shared_ptr<ClientInfo> client);
	void removeClient(ClientInfo& client);
	int getClientsAmount() const { return static_cast<int>(clients.size()); }
	bool hasClient(ClientInfo& client);

	Player& otherPlayer(Player& player);

	vector<string> getCharacterOrder() const { return characterOrder; };

	void shuffleBuildings();
	unique_ptr<Building> getBuilding();
	void returnBuilding(unique_ptr<Building> building);

	auto charactersBegin() { return characters.begin(); }
	auto charactersEnd() { return characters.end(); }
	void removeCharacter(vector<unique_ptr<Character>>::iterator it) { characters.erase(it); }

	bool hasState() { return (!!currentState); };
	State& getCurrentState() { return *currentState; };
	void showState();

	void start();
	void startRound();
	void endRound();
	bool isFinished() const { return finished; }

	void callNextCharacter(string lastCharacter = "");
	void resetCharacters();

	void notifyAllPlayers(string message = "");
	void allPrompt();

private:

	bool finished = false;

	vector<shared_ptr<ClientInfo>> clients;
	weak_ptr<ClientInfo> firstWon;


	CharacterFactory characterFactory;
	BuildingFactory buildingFactory;

	vector<unique_ptr<Building>> buildings;
	vector<unique_ptr<Building>> returnedBuildings;

	vector<unique_ptr<Character>> characters;
	vector<string> characterOrder;

	unique_ptr<State> currentState;




};


