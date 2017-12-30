#pragma once

#include <string>


using namespace std;

class Game;
class Player;
class State {


public:


	virtual void processState(Game& game, Player& player, string command) {};

	virtual void printOptions(Game& game, Player& player) {};


private:




};



