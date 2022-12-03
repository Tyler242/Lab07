#include <cmath>
#include <iostream>
#include "Velocity.h"
Velocity::Velocity() {
	dx = 0;
	dy = 0;
	v = 0;
}

Velocity::Velocity(double v, double angle) {
	this->dx = v * sin(angle);
	std::cout << dx;
	if (dx > 0.0)
		direction = '+';
	else if (dx < 0)
		direction = '-';
	else
		direction = '^';
	this->dy = v * cos(angle);
	this->v = v;
}

void Velocity::computeVelocity(double ddx, double ddy, double t) {
	switch (direction)
	{
	case '+':
		if (this->dx > 0)
			this->dx = dx + ddx * t;
		else
			this->dx = 0;
		break;
	case '-':
		if (this->dx < 0)
			this->dx = dx + ddx * t;
		else
			this->dx = 0;
		break;
	default:
		this->dx = 0;
		break;
	}
	this->dy = dy + ddy * t;
	this->v = sqrt((dx * dx) + (dy * dy));
}