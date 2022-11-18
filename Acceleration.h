#pragma once
#include "Force.h"
class Acceleration
{
public:
	Acceleration();
	Acceleration(const double angle);
	void computeAcceleration(const double altitude, const double velocity, const double time);
	double getDDX() const {
		return ddx;
	}
	double getDDY() const {
		return ddy;
	}
private:
	double ddx;
	double ddy;
	double totalAccel;
	double angle;
	Force force;
	double computeGravity(const double altitude);
	friend class TestAcceleration;
};

