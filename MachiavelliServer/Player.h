//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>

class Player {
public:
    Player() {}
    Player(const std::string& name) : name {name} {}

    std::string get_name() const { return name; }
    void set_name(const std::string& new_name) { name = new_name; }

	bool hasMessage() { return (recievingMessage != ""); };
	std::string getMessage() const { return recievingMessage; };
	void messageRecieved() { recievingMessage = ""; };

	void notify(std::string message) { recievingMessage = message; }

	bool isWaiting() const { return waiting; }
	void setWaiting(bool setWait) { waiting = setWait; }

private:
    std::string name;

	int coins;

	std::string recievingMessage = "";

	bool waiting = false;

};

#endif /* Player_hpp */
