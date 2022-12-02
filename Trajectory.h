#pragma once
#include <vector>
#include "position.h"
#include "Constants.cpp";

using namespace std;

class Trajectory
{
private:
	vector<tuple<Position, double>> projectileArray;
	int maxLength = MAX_SHADOW;
};

