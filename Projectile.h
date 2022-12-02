#pragma once
#include "position.h"
#include "Velocity.h"
#include "Acceleration.h"
#include "uiDraw.h"
#include "ground.h"

class Projectile
{
private:
	Position position;
	Velocity v;
	Acceleration a;
	bool flying;
	bool onTarget;
	double age;
	double angle;
public:
	Projectile();
	Projectile(const Position position, double angle);
	Position getPos() const {
		return position;
	}
	double getSpeed() const {
		return v.getVelocity();
	}
	double getAge() const {
		return age;
	}
	bool isFlying() const {
		return flying;
	}
	bool isLandedOnTarget() const {
		return this->onTarget;
	}
	void move();
	void hitGround(Ground& ground);
	void hitTarget(Ground& ground);
};

