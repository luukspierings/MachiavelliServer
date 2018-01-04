#include "stdafx.h"
#include "Building.h"

string Building::getPrint()
{
	return "(" + to_string(points) + ") " + name + " [" + cardColorToString() + "]";
}

string Building::cardColorToString()
{
	switch (color) {
	case CardColor::NONE: return "white";
	case CardColor::YELLOW: return "yellow";
	case CardColor::BLUE: return "blue";
	case CardColor::GREEN: return "green";
	case CardColor::RED: return "red";
	case CardColor::LILAC: return "lilac";
	default: return "";
	}
}