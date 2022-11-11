#pragma once
#include "MapReader.h"
class Force
{
public:
	Force();
	void computeForce(const double altitude, const double velocity);
	double getForce() const {
		return force;
	}
private:
	double force;
	double computeSpeedOfSound(const double altitude);
	double computeDragCoef(const double speed);
	double computeAirDensity(const double altitude);
	friend class TestForce;
};