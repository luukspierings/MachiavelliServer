#include "stdafx.h"
#include "BuildingFactory.h"
#include "BuildingDeck.h"

vector<unique_ptr<Building>> BuildingFactory::getBuildings()
{
	BuildingDeck bDeck;
	std::ifstream stream("Bouwkaarten.csv");
	stream >> bDeck;

	vector<unique_ptr<Building>> buildings{};

	vector<vector<string>> data = fileHandler.getValues();

	for (auto row : data) {
		
		CardColor color = CardColor::NONE;

		if (row[2] == "geel") color = CardColor::YELLOW;
		if (row[2] == "groen") color = CardColor::GREEN;
		if (row[2] == "blauw") color = CardColor::BLUE;
		if (row[2] == "rood") color = CardColor::RED;
		//if (row[2] == "lila") color = CardColor::LILAC;

		if (color != CardColor::NONE) {
			buildings.push_back(make_unique<Building>(row[0], stoi(row[1]), color));
		}

	}

	return buildings;

}
