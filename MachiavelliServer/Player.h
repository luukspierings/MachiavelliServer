//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Character.h"
#include "Building.h"

#include "BuildingHand.h"
#include "CharacterHand.h"


using namespace std;

class Player {
public:
	Player() { reset(); }
	Player(const string& name) : name{ name } { reset(); }

    string get_name() const { return name; }
    void set_name(const string& new_name) { name = new_name; }

	bool hasMessages();
	vector<string> getMessages();

	void notify(string message = "");
	void write(string message = "");
	void prompt();

	bool isWaiting() const { return waiting; }
	void setWaiting(bool setWait) { waiting = setWait; }

	bool isKing() const { return king; }
	void setKing(bool setKing) { king = setKing; }

	int getCoins() const { return coins; }
	void earnCoins(int earning) { if (earning > 0) { coins += earning; } }
	int stealCoins() { int c = coins; coins = 0; return c; }
	void loseCoins(int losing) { if (losing > 0) { coins -= losing; } }

	int countPoints();
	int countBuildingPoints();

	void resetRound();
	void reset();

	bool isFinished() const;

	bool isPreached() const { return preached; }
	void preach() { preached = true; }

	BuildingHand& getHandBuildings() { return handBuildings; };
	BuildingHand& getBuiltBuildings() { return builtBuildings; };
	void buyBuilding(string buildingName);
	
	CharacterHand& getCharacterHand() { return characters; };
	bool hasCharacter(Character * character);

private:
    string name;
	vector<string> messageQueue{};
	vector<string> messages{};

	int coins;
	bool king;
	bool preached;

	BuildingHand handBuildings;
	BuildingHand builtBuildings;

	CharacterHand characters;

	bool waiting;

};

