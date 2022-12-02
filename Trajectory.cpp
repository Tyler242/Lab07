#include "Trajectory.h"
#include "Constants.cpp";

Trajectory::Trajectory() {
	maxLength = MAX_SHADOW;
	projectileArray = {};
};

bool Trajectory::addProjectile(Projectile& projectile) {
	if (projectileArray.size() >= maxLength)
		return false;

	try {
		tuple<Position, double> projTuple(projectile.getPos(), projectile.getAge());
		projectileArray.push_back(projTuple);
		return true;
	}
	catch (char * str) {
		return false;
	}
}