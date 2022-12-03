#include "Projectile.h"
#include "Constants.cpp"

Projectile::Projectile() {
	angle = 0;
	position = Position();
	v = Velocity(I_VELOCITY, angle);
	a = Acceleration(angle);
	age = 0;
}

Projectile::Projectile(const Position position, double angle) {
	this->position = position;
	this->angle = angle;
	v = Velocity(I_VELOCITY, angle);
	a = Acceleration(angle);
	age = 0;
}

void Projectile::move() {
	a.computeAcceleration(position.getMetersY(), v.getVelocity(), TIME_INTERVAL);
	v.computeVelocity(a.getDDX(), a.getDDY(), TIME_INTERVAL);
	
	position.addMetersX(
		v.getDX() * TIME_INTERVAL 
		+ 0.5 * a.getDDX() * TIME_INTERVAL * TIME_INTERVAL
	);
	
	position.addMetersY(
		v.getDY() * TIME_INTERVAL
		+ 0.5 * a.getDDY() * TIME_INTERVAL * TIME_INTERVAL
	);
}