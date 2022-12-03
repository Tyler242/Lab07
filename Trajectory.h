#pragma once
#include <list>
#include "position.h"
#include "Projectile.h"
#include "ProjectileData.h"

using namespace std;

class Trajectory
{
private:
	list<ProjectileData> projectileArray;
	int maxLength;
public:
	Trajectory();
	void addProjectile(Projectile projectile);
	int getMaxLength() const {
		return maxLength;
	}
	void reset() {
		projectileArray.clear();
	}
	void draw(ogstream& gout) const {
		for (auto it = projectileArray.begin(); it != projectileArray.end(); it++) {
			gout.drawProjectile(it->position, it->age);
		};
	}
};