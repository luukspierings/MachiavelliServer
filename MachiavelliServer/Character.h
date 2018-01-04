#pragma once

#include <string>
#include <memory>
#include <vector>
#include "CardColor.h"
#include "State.h"
#include "Building.h"

using namespace std;

class Game;
class Player;
class Character : public State
{
public:
	Character() {};

	virtual ~Character() = default;

	virtual void kill() { dead = true; };
	bool isDead() const { return dead; };


	virtual void steal() { stolen = true; };

	string getName() const { return name; };


	virtual void printOptions(Game& game, Player& player) override;
	virtual void processState(Game& game, Player& player, string command) override;


protected:

	CardColor color = CardColor::NONE;
	string name = "empty character";

	bool dead = false;
	bool stolen = false;


	virtual void printOverview(Game & game, Player & player) override;

	// choosing between the 2 default options: 2 coins or 1 building
	bool performedDefault = false;
	virtual void defaultOptions(Game & game, Player & player);

	// choosing the building and discarding 1
	bool choosingBuildingCard = false;
	vector<unique_ptr<Building>> buildingCards{};
	virtual void chooseBuildingOptions(Game & game, Player & player);

	// choosing the building to build
	bool performedBuilding = false;
	bool choosingBuild = false;
	virtual void buildOptions(Game & game, Player & player);

	// choosing the character specific option
	bool performedCharacter = false;
	virtual void characterOptions(Game & game, Player & player) {};

};

