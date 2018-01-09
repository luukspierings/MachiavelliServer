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
	Character() { reset(); };
	Character(int pOrder) : order(pOrder) { reset(); };

	virtual ~Character() = default;

	virtual void kill() { dead = true; };
	bool isDead() const { return dead; };

	virtual void steal() { stolen = true; };
	bool isStolen() const { return stolen; };

	string getName() const { return name; };
	string getDescription() const { return description; };

	virtual void startCharacter(Game& game, Player& player);

	virtual void printOptions(Game& game, Player& player) override;
	virtual void processState(Game& game, Player& player, string command) override;

	int getOrder() const { return order; }

	void choose() { chosen = true; }
	bool isChosen() const { return chosen; }

	void reset();

protected:

	int order = 0;
	CardColor color = CardColor::NONE;
	string name = "empty character";
	string description = "-";

	bool chosen;

	bool dead;
	bool stolen;


	virtual void printOverview(Game & game, Player & player) override;

	// choosing between the 2 default options: 2 coins or 1 building
	bool performedDefault = false;
	virtual void defaultOptions(Game & game, Player & player);

	// choosing the building and discarding 1
	bool choosingBuildingCard = false;
	vector<Building> buildingCards{};
	virtual void chooseBuildingOptions(Game & game, Player & player);

	// choosing the building to build
	int buildingsBuilt = 0;
	int maxBuilding = 1;
	bool choosingBuild = false;
	virtual void buildOptions(Game & game, Player & player);

	// choosing the character specific option
	bool performedCharacter = false;
	virtual void characterOptions(Game & game, Player & player) {};

};

