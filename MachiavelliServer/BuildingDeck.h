#pragma once

#include "Deck.h"
#include "Building.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>
#include <vector>

class BuildingDeck : public Deck<Building> {

public:
	friend std::ifstream& operator>>(std::ifstream & ifstream, BuildingDeck& characterDeck);

private:

};
