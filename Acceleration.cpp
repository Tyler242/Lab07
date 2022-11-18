#include <cassert>
#include <cmath>
#include "Acceleration.h"

#define PROJECTILE_MASS 46.7;

Acceleration::Acceleration() {
	ddx = 0;
	ddy = 0;
	totalAccel = 0;
	angle = 0;
}

Acceleration::Acceleration(const double angle) {
	ddx = 0;
	ddy = 0;
	totalAccel = 0;
	this->angle = angle;
}

double Acceleration::computeGravity(const double altitude) {
	if (altitude > 25000)
		throw exception("Altitude is too large");

	map<double, double> gravityMap{
		{0, 9.807},
		{1000,9.804},
		{2000,9.801},
		{3000,9.797},
		{4000,9.794},
		{5000,9.791},
		{6000,9.788},
		{7000,9.785},
		{8000,9.782},
		{9000,9.779},
		{10000,9.776},
		{15000,9.761},
		{20000,9.745},
		{25000,9.730}
	};

	double gravity = MapReader().getMapValue(altitude, gravityMap);

	if (gravity < 9 || gravity > 9.9)
		throw exception("Gravity value out of bounds");

	return gravity;
}

void Acceleration::computeAcceleration(const double altitude, const double velocity, const double time) {
	// compute and get the force
	this->force.computeForce(altitude, velocity);
	double dragForce = force.getForce();

	// compute total acceleration: f / m = a
	this->totalAccel = dragForce / PROJECTILE_MASS;

	// compute gravity
	double gravityForce = computeGravity(altitude);

	// compute individual acceleration components
	this->ddx = -totalAccel * sin(this->angle);
	this->ddy = -totalAccel * cos(this->angle) - gravityForce;
}