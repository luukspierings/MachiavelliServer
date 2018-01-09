#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <random>

#include "Building.h"
#include "Character.h"
#include "State.h"
#include "ClientInfo.h"
#include "RandomGenerator.h"

#include "DeckFactory.h"
#include "BuildingDeck.h"
#include "CharacterHand.h"

#include "ChooseCharacter.h"

using namespace std;

class Game
{

public:

	Game() {
		deckFactory.loadBuildingDeck(buildingDeck);
		deckFactory.loadCharacterHand(characterHand);
	};

	void addClient(shared_ptr<ClientInfo> client);
	void removeClient(ClientInfo& client);
	int getClientsAmount() const { return static_cast<int>(clients.size()); }
	bool hasClient(ClientInfo& client);

	Player& otherPlayer(Player& player);

	bool hasState() { return (!!currentState); };
	State& getCurrentState() { return *currentState; };
	void showState();

	void start();
	void startRound();
	void endRound();
	bool isFinished() const { return finished; }

	void callNextCharacter();

	void notifyAllPlayers(string message = "");
	void allPrompt();

	BuildingDeck& getBuildingDeck() { return buildingDeck; };
	CharacterHand& getCharacterHand() { return characterHand; };


private:

	bool finished = false;

	vector<shared_ptr<ClientInfo>> clients;
	weak_ptr<ClientInfo> firstWon;

	DeckFactory deckFactory;
	BuildingDeck buildingDeck;
	CharacterHand characterHand;

	shared_ptr<State> currentState;

};


