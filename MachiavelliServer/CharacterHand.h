#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "Hand.h"
#include "Deck.h"
#include "Character.h"

using namespace std;

class CharacterHand: public Hand<Character> {

public:

	friend ifstream& operator>>(ifstream& ifstream, CharacterHand& characterHand);

	Character makeCharacter(string name, int order);

	void sortCharacters();

private:


};
