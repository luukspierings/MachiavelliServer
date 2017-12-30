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
	return (recievingMessage.size() > 0);
}

vector<string> Player::getMessages()
{
	lock.lock();

	vector<string> messages{ recievingMessage };
	recievingMessage.clear();

	lock.unlock();
	return messages;
}

void Player::notify(string message) {
	lock.lock(); 

	recievingMessage.push_back(message); 

	lock.unlock(); 
}

bool Player::hasCharacter(string characterName)
{
	for (const auto & c : characters) {
		if (c->getName() == characterName) return true;
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
			}
			else {
				notify("You don't have enough coins to buy this building!");
			}
		}
	}
}
