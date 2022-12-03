#include "Trajectory.h"
#include "Constants.cpp"
#include "ProjectileData.h"

Trajectory::Trajectory() {
	maxLength = MAX_SHADOW;
	projectileArray = {};
};

void Trajectory::addProjectile(Projectile projectile) {
	for (auto it = projectileArray.begin(); it != projectileArray.end(); it++) {
		it->age += TIME_INTERVAL;
	}

	if (projectileArray.size() == maxLength) {
		projectileArray.pop_back();

		ProjectileData data(projectile.getPos(), projectile.getAge());
		projectileArray.push_front(data);
	}
	else if (projectileArray.size() < maxLength) {
		ProjectileData data(projectile.getPos(), projectile.getAge());
		projectileArray.push_front(data);
	}
}