#pragma once

#include <string>

#include "CardColor.h"


using namespace std;

class Building
{
public:
	Building(string name, int points, CardColor color) : 
		name(name), 
		points(points), 
		cost(points), 
		color(color) {};

	string getName() const { return name; }
	int getCost() const { return cost; }
	int getDestroyCost() const { return cost - 1; }
	int getPoints() const { return points; }
	CardColor getColor() const { return color; }

	string getPrint();




private:

	string name;

	int points;
	int cost;

	CardColor color;

	string cardColorToString();
};

