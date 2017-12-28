#pragma once

#include <memory>
#include <vector>

#include "Character.h"

#include "Assassin.h"
#include "Builder.h"
#include "Condottiere.h"
#include "King.h"
#include "Mage.h"
#include "Merchant.h"
#include "Preacher.h"
#include "Robber.h"
#include "FileHandler.h"

using namespace std;

class CharacterFactory {


public:

	vector<unique_ptr<Character>> getCharacters();


private:

	FileHandler fileHandler{ "karakterkaarten.csv" };



};

