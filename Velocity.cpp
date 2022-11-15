#include <cmath>
#include "Velocity.h"
Velocity::Velocity() {
	dx = 0;
	dy = 0;
	v = 0;
}

Velocity::Velocity(double dx, double dy) {
	this->dx = dx;
	this->dy = dy;
	this->v = sqrt((dx * dx) + (dy * dy));
}

void Velocity::computeVelocity(double ddx, double ddy, double t) {
	this->dx = dx + ddx * t;
	this->dy = dy + ddy * t;
	this->v = sqrt((dx * dx) + (dy * dy));
}