#pragma once

#include <memory>
#include <vector>

#include "Building.h"

#include "FileHandler.h"

using namespace std;

class BuildingFactory {


public:

	vector<unique_ptr<Building>> getBuildings();


private:

	FileHandler fileHandler{ "Bouwkaarten.csv" };



};

