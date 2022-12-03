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
	bool isFlying(const Ground ground) const {
		if (position.getMetersY() > ground.getElevationMeters(position)) {
			return true;
		}
		else {
			return false;
		}
	}

	void move();
};
