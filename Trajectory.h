#pragma once
#include <vector>
#include "position.h"
#include "Projectile.h"

using namespace std;
using std::get;

class Trajectory
{
private:
	vector<tuple<Position, double>> projectileArray;
	int maxLength;
public:
	Trajectory();
	bool addProjectile(Projectile& projectile);
	int getMaxLength() const {
		return maxLength;
	}
	void reset() {
		projectileArray.clear();
	}
	void draw(ogstream& gout) const {
		for (auto it = projectileArray.begin(); it != projectileArray.end(); it++) {
			gout.drawProjectile(get<0>(*it), get<1>(*it));
		};
	}
};