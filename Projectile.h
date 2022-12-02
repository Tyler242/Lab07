#pragma once
#include "position.h"
#include "Velocity.h"
#include "Acceleration.h"
#include "uiDraw.h"

class Projectile
{
private:
	Position position;
	Velocity v;
	Acceleration a;
	bool flying;
	double age;

public:
	Projectile();
	Projectile(Position& position);
	double getPosX() const {
		return position.getMetersY();
	}
	double getPosY() const {
		return position.getMetersX();
	}
	double getSpeed() const {
		return v.getVelocity();
	}
	double getAge() const {
		return age;
	}
	bool isFlying() const {
		return isFlying;
	}
	void draw(ogstream& gout) const {
		gout.drawProjectile(position, age);
	}
	void move();
	void hitGround();
	void hitTarget();
	void reset();
};

