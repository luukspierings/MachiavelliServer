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

bool Player::hasCharacter(Character* character)
{
	if (character == nullptr) return false;
	for (auto& it = characters.handBegin(); it != characters.handEnd(); it++) {
		if ((*it)->getName() == character->getName() && !(*it)->isDead()) return true;
	}
	return false;
}
//
//void Player::putCharacter(unique_ptr<Character> character)
//{
//	characters.push_back(move(character));
//}
//
//unique_ptr<Character> Player::pullCharacter(string characterName)
//{
//	unique_ptr<Character> buf;
//	for (auto it = characters.begin(); it != characters.end(); it++) {
//		if ((*it)->getName() == characterName) {
//			buf = move(*it);
//			characters.erase(it);
//			break;
//		}
//	}
//	return buf;
//}
//
//void Player::putBuilding(unique_ptr<Building> building)
//{
//	handBuildings.push_back(move(building));
//}
//
//unique_ptr<Building> Player::pullBuilding(string buildingName)
//{
//	unique_ptr<Building> buf;
//	for (auto it = handBuildings.begin(); it != handBuildings.end(); it++) {
//		if ((*it)->getName() == buildingName) {
//			buf = move(*it);
//			handBuildings.erase(it);
//			break;
//		}
//	}
//	return buf;
//}

void Player::buyBuilding(string buildingName)
{
	for (auto& it = handBuildings.handBegin(); it != handBuildings.handEnd(); it++) {
		if (it->getName() == buildingName) {

			int cost = it->getCost();

			if (coins >= cost) {
				coins -= cost;
				builtBuildings.push_top_stack(move(handBuildings.handPull(it)));
				break;
			}
			else {
				notify("You don't have enough coins to buy this building!");
			}
		}
	}
}
//
//unique_ptr<Building> Player::destroyBuilding(string buildingName)
//{
//	unique_ptr<Building> buf;
//	for (auto it = stackBuildings.begin(); it != stackBuildings.end(); it++) {
//		if ((*it)->getName() == buildingName) {
//			buf = move(*it);
//			stackBuildings.erase(it);
//			break;
//		}
//	}
//	return buf;
//}

int Player::countPoints()
{
	int points = 0;

	// first all individual points
	points += countBuildingPoints();

	// second if player has all color buildings
	bool hasAllColors = true;
	vector<CardColor> minimumColors{ CardColor::BLUE, CardColor::GREEN, CardColor::RED, CardColor::YELLOW, CardColor::LILAC };
	vector<CardColor> colors{};

	for (auto& it = builtBuildings.handBegin(); it != builtBuildings.handEnd(); it++) {
		if (find(colors.begin(), colors.end(), it->getColor()) == colors.end()) colors.push_back(it->getColor());
	}
	for (auto & minColor : minimumColors) {
		if (find(colors.begin(), colors.end(), minColor) == colors.end()) hasAllColors = false;
	}
	if (hasAllColors) points += 3;

	return points;
}

int Player::countBuildingPoints()
{
	int points = 0;
	for (auto& it = builtBuildings.handBegin(); it != builtBuildings.handEnd(); it++) {
		points += it->getPoints();
	}
	return points;
}

void Player::resetRound()
{
	waiting = (!king);
	preached = false;
}

void Player::reset()
{
	coins = 0;
	king = false;
	preached = false;
	waiting = false;
}

bool Player::isFinished() const
{
	return (builtBuildings.handAmount() >= 8);
}
