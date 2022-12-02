#include "Projectile.h"
#include "Constants.cpp"

Projectile::Projectile() {
	position = Position();
	v = Velocity();
	a = Acceleration();
	flying = false;
	age = 0;
}

Projectile::Projectile(Position& newPosition) {
	position = newPosition;
	v = Velocity();
	a = Acceleration();
	flying = false;
	age = 0;
}

void Projectile::move() {
	a.computeAcceleration(position.getMetersY(), I_VELOCITY, TIME_INTERVAL);
	v.computeVelocity(a.getDDX(), a.getDDY(), TIME_INTERVAL);
	position.addMetersX(
		position.getMetersX() 
		+ v.getDX() * TIME_INTERVAL 
		+ 0.5 * a.getDDX() * TIME_INTERVAL * TIME_INTERVAL
	);
	position.addMetersY(
		position.getMetersY()
		+ v.getDY() * TIME_INTERVAL
		+ 0.5 * a.getDDY() * TIME_INTERVAL * TIME_INTERVAL
	);
}