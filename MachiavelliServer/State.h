#pragma once

#include <string>


using namespace std;

class Game;
class Player;
class State {

public:

	virtual ~State() = default;

	virtual void processState(Game& game, Player& player, string command) = 0;
	virtual void printOverview(Game& game, Player& player) {};
	virtual void printOptions(Game& game, Player& player) = 0;

private:

};



