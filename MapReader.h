#include <map>
#pragma once

using namespace std;

static class MapReader
{
public:
	double getMapValue(double value, map<double, double>& map);
private:
	double linearInterpolation(double d0, double r0, double d1, double r1, double d);

	friend class TestForce;
	friend class TestAcceleration;
};