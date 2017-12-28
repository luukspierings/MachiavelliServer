#pragma once

#include <string>
#include "CardColor.h"
#include "State.h"

using namespace std;

class Character : public State
{
public:
	Character() {};
	virtual	~Character() {};

	virtual void kill() {
		isDead = true;
	};

	const string getName() {
		return name;
	}

protected:

	bool isDead = false;
	bool isCalled = false;

	CardColor color = CardColor::NONE;

	string name = "empty character";

};

