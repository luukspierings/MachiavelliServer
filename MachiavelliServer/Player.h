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

using namespace std;

class Player {
public:
    Player() {}
	Player(const string& name) : name{ name } {}
	//Player(const Player& player);

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

	bool hasCharacter(string characterName);
	void putCharacter(unique_ptr<Character> character);
	unique_ptr<Character> pullCharacter(string characterName);

	void putBuilding(unique_ptr<Building> building);
	void buyBuilding(string buildingName);

	auto charactersBegin() { return characters.begin(); }
	auto charactersEnd() { return characters.end(); }

	auto handBuildingsBegin() const { return handBuildings.begin(); }
	auto handBuildingsEnd() const { return handBuildings.end(); }

	auto stackBuildingsBegin() const { return stackBuildings.begin(); }
	auto stackBuildingsEnd() const { return stackBuildings.end(); }
	int stackBuildingsAmount() const { return stackBuildings.size(); }

	int getCoins() const { return coins; }
	void earnCoins(int earning) { if (earning > 0) { coins += earning; } }

	int countPoints() const;
	int countBuildingPoints() const;

	void resetRound();

	bool isFinished() const;

private:
    string name;
	vector<string> messageQueue{};
	vector<string> messages{};

	int coins = 0;
	bool king = false;
	vector<unique_ptr<Character>> characters;
	vector<unique_ptr<Building>> handBuildings;
	vector<unique_ptr<Building>> stackBuildings;

	bool waiting = false;

};

