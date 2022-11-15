#pragma once
class Velocity
{
public:
	Velocity();
	Velocity(double dx, double dy);
	void computeVelocity(const double ddx, const double ddy, double time);
	double getDX() const {
		return dx;
	}
	double getDY() const {
		return dy;
	}
	double getVelocity() {
		return v;
	}
private:
	double dx;
	double dy;
	double v;

	friend class TestVelocity;
};

