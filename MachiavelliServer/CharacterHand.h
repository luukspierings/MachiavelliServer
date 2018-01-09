#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Hand.h"
#include "Character.h"

using namespace std;

class CharacterHand: public Hand<Character> {

public:

	friend ifstream& operator>>(ifstream& ifstream, CharacterHand& characterHand);


private:

	void sortOrder();

};
