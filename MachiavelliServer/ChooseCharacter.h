#pragma once

#include <string>
#include <memory>

#include "State.h"
#include "Player.h"
#include "Game.h"

using namespace std;

class ChooseCharacter : public State {

public:

	void processState(Game& game, Player& player, string command) override;

	void printOptions(Game& game, Player& player) override;


private:

	bool choosingHand = true;

	bool allCharactersChosen(Game& game, Player& player);

};


