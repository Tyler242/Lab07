#include <map>
#pragma once

using namespace std;

static class MapReader
{
public:
	double getMapValue(double value, map<double, double> map) {
		// catch any values that are too small.
		if (value < map.begin()->first)
			return -1;

		// in case the value equals the max key in the map
		auto it = map.end();
		it--;
		if (value == it->first)
		{
			double d1 = it->first;
			double r1 = it->second;

			it--;
			double d0 = it->first;
			double r0 = it->second;

			return linearInterpolation(d0, r0, d1, r1, value);
		}
		// iterate through the map to find the surrounding points
		// and perform linear interpolation to find the right value.
		for (auto it = map.begin(); it != map.end(); it++) {
			if (value < it->first) {
				double d1 = it->first;
				double r1 = it->second;
				
				it--;
				double d0 = it->first;
				double r0 = it->second;

				return linearInterpolation(d0, r0, d1, r1, value);
			}
		}
		return -1;
	}
private:
	double linearInterpolation(double d0, double r0, double d1, double r1, double d) {
		// (r - r0)/(d - d0) = (r1 - r0)/(d1 - d0)
		// r - r0 = ((r1 - r0)*(d - d0))/(d1 - d0)
		// r = ((r1 - r0)*(d - d0))/(d1 - d0) + r0
		return ((r1 - r0) * (d - d0)) / (d1 - d0) + r0;
	}
	friend class TestForce;
	friend class TestAcceleration;
};

