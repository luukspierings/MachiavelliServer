//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "stdafx.h"

#include "Player.h"




bool Player::hasMessages()
{
	return (messages.size() > 0);
}

vector<string> Player::getMessages()
{
	vector<string> msgs{ messages };
	messages.clear();
	return msgs;
}

void Player::notify(string message) {
	if (messageQueue.size() <= 0) write("\r\n\r\n");
	write(message + "\r\n");
}
void Player::write(string message) {
	messageQueue.push_back(message);
}
void Player::prompt() {
	if (messageQueue.size() > 0) {
		notify();
		write("Machiavelli: " + name + "> ");
		messages.clear();
		swap(messageQueue, messages);
	}
}

bool Player::hasCharacter(string characterName)
{
	for (const auto & c : characters) {
		if (c->getName() == characterName && !c->isDead()) return true;
	}
	return false;
}

void Player::putCharacter(unique_ptr<Character> character)
{
	characters.push_back(move(character));
}

unique_ptr<Character> Player::pullCharacter(string characterName)
{
	unique_ptr<Character> buf;
	for (auto it = characters.begin(); it != characters.end(); it++) {
		if ((*it)->getName() == characterName) {
			buf = move(*it);
			characters.erase(it);
			break;
		}
	}
	return buf;
}

void Player::putBuilding(unique_ptr<Building> building)
{
	handBuildings.push_back(move(building));
}

void Player::buyBuilding(string buildingName)
{
	for (auto it = handBuildings.begin(); it != handBuildings.end(); it++) {
		if ((*it)->getName() == buildingName) {

			int cost = (*it)->getCost();

			if (coins >= cost) {
				coins -= cost;
				stackBuildings.push_back(move(*it));
				handBuildings.erase(it);
				break;
			}
			else {
				notify("You don't have enough coins to buy this building!");
			}
		}
	}
}

int Player::countPoints() const
{
	int points = 0;

	// first all individual points
	points += countBuildingPoints();

	// second if player has all color buildings
	bool hasAllColors = true;
	vector<CardColor> minimumColors{ CardColor::BLUE, CardColor::GREEN, CardColor::RED, CardColor::YELLOW, CardColor::LILAC };
	vector<CardColor> colors{};
	for (auto & building : stackBuildings) {
		if (find(colors.begin(), colors.end(), building->getColor()) == colors.end()) colors.push_back(building->getColor());
	}
	for (auto & minColor : minimumColors) {
		if (find(colors.begin(), colors.end(), minColor) == colors.end()) hasAllColors = false;
	}
	if (hasAllColors) points += 3;

	return points;
}

int Player::countBuildingPoints() const
{
	int points = 0;
	for (auto & building : stackBuildings) {
		points += building->getPoints();
	}
	return points;
}

void Player::resetRound()
{
	characters.clear();
	waiting = (!king);
}

bool Player::isFinished() const
{
	return (stackBuildingsAmount() >= 8);
}
