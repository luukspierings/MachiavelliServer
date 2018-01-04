#pragma once

#include <memory>
#include <vector>

#include "Character.h"

#include "FileHandler.h"

using namespace std;

class CharacterFactory {


public:

	vector<unique_ptr<Character>> getCharacters();


private:




};

