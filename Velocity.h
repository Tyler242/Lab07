#pragma once
class Velocity
{
public:
	Velocity();
	Velocity(double v, double angle);
	void computeVelocity(const double ddx, const double ddy, double time);
	double getDX() const {
		return dx;
	}
	double getDY() const {
		return dy;
	}
	double getVelocity() const {
		return v;
	}
private:
	double dx;
	double dy;
	double v;
	char direction;

	friend class TestVelocity;
};

