#pragma once
#include <cassert>
#include <iostream>
#include <string>
#include "Acceleration.h"

using namespace std;
class TestAcceleration
{
public:
	void run() {
		cout << "Running Acceleration Tests" << endl;

		// computeGravity(double altitude) tests
		TestComputeGravity_AltUpperBound();
		TestComputeGravity_AltMidVal();
		TestComputeGravity_AltMidBound();
		TestComputeGravity_AltLowBound();
		TestComputeGravity_AltTooHigh();

		// computeAcceleration(altitude, velocity, time) tests
		TestComputeAcceleration_FiringAccel();
		TestComputeAcceleration_UpperAlt();

		cout << "Acceleration Tests Passed" << endl;
	}

private:
	void TestComputeGravity_AltUpperBound() {
		// setup 
		Acceleration acceleration;
		double altitude = 25000;
		double expectedGravity = MapReader().linearInterpolation(20000, 9.745, 25000, 9.730, 25000);

		// exercise
		double gravity = acceleration.computeGravity(altitude);

		// verify
		assert(gravity == expectedGravity, "TestComputeGravity_AltUpperBound() Failed");

		// teardown
	}
	void TestComputeGravity_AltMidVal() {
		// setup
		Acceleration acceleration;
		double altitude = 8345;
		double expectedGravity = MapReader().linearInterpolation(8000, 9.782, 9000, 9.779, altitude);
		
		// exercise
		double gravity = acceleration.computeGravity(altitude);

		// verify
		assert(gravity == expectedGravity, "TestComputeGravity_AltMidVal Failed");
		
		// teardown
	}
	void TestComputeGravity_AltMidBound() {
		// setup
		Acceleration acceleration;
		double altitude = 7000;
		double expectedGravity = MapReader().linearInterpolation(7000, 9.785, 8000, 9.782, altitude);

		// exercise
		double gravity = acceleration.computeGravity(altitude);

		// verify
		assert(gravity == expectedGravity, "TestComputeGravity_AltMidBound Failed");

		// teardown
	}
	void TestComputeGravity_AltLowBound() {
		// setup
		Acceleration acceleration;
		double altitude = 0;
		double expectedGravity = 9.807;

		// exercise
		double gravity = acceleration.computeGravity(altitude);

		// verify
		assert(gravity == expectedGravity, "TestComputeGravity_AltLowBound Failed");

		// teardown
	}
	void TestComputeGravity_AltTooHigh() {
		// setup
		Acceleration acceleration;
		double altitude = 25001;
		string expErrString = "Altitude is too large";

		// exercise
		try {
			double gravity = acceleration.computeGravity(altitude);
		}
		catch (exception& ex) {
		// verify
			string errString = ex.what();
			assert(errString == expErrString, "TestComputeGravity_AltTooHigh Failed");
		}

		// teardown
	}

	void TestComputeAcceleration_FiringAccel() {
		// setup
		Acceleration accel = Acceleration((45.0 / 360.0) * (2.0 * 3.14159));
		double altitude = 0;
		double velocity = 827;
		double time = 0.1;
		double expectedDDX;
		double expectedDDY;
		double expectedA;

		// exercise
		accel.computeAcceleration(altitude, velocity, time);

		// verify
		assert(accel.ddx == -31.018786539924552);
		assert(accel.ddy == -40.825827695519536);
		assert(accel.totalAccel == 43.867217714527264);

		// teardown
	}
	void TestComputeAcceleration_UpperAlt() {
		// setup
		Acceleration accel;
		double altitude = 24000;
		double velocity = 100;
		double time = 0.1;

		// exercise
		accel.computeAcceleration(altitude, velocity, time);

		// verify
		assert(accel.ddx == -0.0);
		assert(accel.ddy == -9.7494398158025906);
		assert(accel.totalAccel == 0.016439815802589245);

		// teardown
	}
};

