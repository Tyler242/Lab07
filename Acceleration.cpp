#include <cassert>
#include <cmath>
#include <iostream>
#include "Acceleration.h"
#include "Constants.cpp"

Acceleration::Acceleration() {
	ddx = 0;
	ddy = 0;
	totalAccel = 0;
	angle = 0;  // in radians
}

Acceleration::Acceleration(const double angle) {
	ddx = 0;
	ddy = 0;
	totalAccel = 0;
	this->angle = angle; // in radians
}

double Acceleration::computeGravity(const double altitude) {
	if (altitude > 25000)
		throw exception("Altitude is too large");

	double gravity = force.computeGravity(altitude);

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