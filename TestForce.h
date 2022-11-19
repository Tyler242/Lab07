#pragma once
/***********************************************************************
 * Header File:
 *    Test Force: Test the Force class
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    All the unit tests for Force
 ************************************************************************/

#include <cassert>
#include "Force.h"

#ifndef NDEBUG
class TestForce
{
public:
	/****************************************************
	* RUN
	* Run all the tests contained in this class.
	*****************************************************/
	void run() {
		cout << "Running Force Tests" << endl;

		TestComputeForce_LowerBoundAlt();
		TestComputeForce_MidAlt();
		TestComputeForce_UpperBoundAlt();
		TestComputeForce_MidV();
		TestComputeForce_LargeV();

		TestComputeSpdOfSnd_LowBound();
		TestComputeSpdOfSnd_MidVal();
		TestComputeSpdOfSnd_MidBound();
		TestComputeSpdOfSnd_UpperBound();

		TestComputeDragCoef_LowBound();
		TestComputeDragCoef_MidVal();
		TestComputeDragCoef_MidBound();
		TestComputeDragCoef_UpperBound();

		TestComputeAirDnsty_LowBound();
		TestComputeAirDnsty_MidVal();
		TestComputeAirDnsty_MidBound();
		TestComputeAirDnsty_UpperBound();

		cout << "Force Tests Passed" << endl;
	}
private:
	/****************************************************
	* TestComputeForce_LowerBoundAlt
	* Test Force::computeForce(altitude, velocity) when 
	* altitude is 0
	*****************************************************/
	void TestComputeForce_LowerBoundAlt() const {
		// setup
		Force * force = new Force();
		// exercise
		force->computeForce(0, 800);
		// verify
		assert(force->getForce() == 1957.0090726610856);
		// teardown
		delete force;
		
	}

	/****************************************************
	* TestComputeForce_MidAlt
	* Test Force::computeForce(altitude, velocity) when
	* altitude is somewhere in the valid range.
	*****************************************************/
	void TestComputeForce_MidAlt() const {
		// setup
		Force* force = new Force();
		// exercise
		force->computeForce(3450, 600);
		// verify
		assert(force->getForce() == 927.60770183937836);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeForce_UpperBoundAlt
	* Test Force::computeForce(altitude, velocity) when
	* altitude is equal to the max key in the map.
	*****************************************************/
	void TestComputeForce_UpperBoundAlt() const {
		// setup
		Force* force = new Force();

		// exercise
		force->computeForce(25000, 150);
		// verify
		assert(force->getForce() == 1.4228849710779314);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeForce_MidV
	* Test Force::computeForce(altitude, velocity) when
	* velocity is a normal mid-range value.
	*****************************************************/
	void TestComputeForce_MidV() const {
		// setup
		Force* force = new Force();
		// exercise
		force->computeForce(10100, 420);
		// verify
		assert(force->getForce() == 260.80376468221181);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeForce_LargeV
	* Test Force::computeForce(altitude, velocity) when
	* velocity is a larger number.
	*****************************************************/
	void TestComputeForce_LargeV() const {
		// setup
		Force* force = new Force();
		// exercise
		force->computeForce(0, 875);
		// verify
		assert(force->force == 2208.2533174262371);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeSpdOfSnd_LowBound
	* Test Force::computeSpeedOfSound(altitude) when
	* altitude is 0.
	*****************************************************/
	void TestComputeSpdOfSnd_LowBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeSpeedOfSound(0);
		// verify
		assert(value == 340);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeSpdOfSnd_MidVal
	* Test Force::computeSpeedOfSound(altitude) when
	* altitude is between two keys in the map.
	*****************************************************/
	void TestComputeSpdOfSnd_MidVal() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeSpeedOfSound(15369);
		// verify
		assert(value == MapReader().linearInterpolation(15000, 295, 20000, 295, 15369));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeSpdOfSnd_MidBound
	* Test Force::computeSpeedOfSound(altitude) when
	* altitude is equal to a key within the map.
	*****************************************************/
	void TestComputeSpdOfSnd_MidBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeSpeedOfSound(9000);
		// verify
		assert(value == MapReader().linearInterpolation(9000, 303, 10000, 299, 9000));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeSpdOfSnd_UpperBound
	* Test Force::computeSpeedOfSound(altitude) when
	* altitude is equal to the max key in the map.
	*****************************************************/
	void TestComputeSpdOfSnd_UpperBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeSpeedOfSound(40000);
		// verify
		assert(value == 324);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeDragCoef_LowBound
	* Test Force::computeDragCoef(speed) when speed
	* is equal to the min key in the map.
	*****************************************************/
	void TestComputeDragCoef_LowBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeDragCoef(0.300);
		// verify
		assert(value == MapReader().linearInterpolation(0.300, 0.1629, 0.500, 0.1659, 0.300));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeDragCoef_MidVal
	* Test Force::computeDragCoef(speed) when speed
	* is between two keys in the map.
	*****************************************************/
	void TestComputeDragCoef_MidVal() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeDragCoef(0.9909);
		// verify
		assert(value == MapReader().linearInterpolation(0.9800, 0.4002, 1.000, 0.4258, 0.9909));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeDragCoef_MidBound
	* Test Force::computeDragCoef(speed) when speed
	* is equal to a key within the map.
	*****************************************************/
	void TestComputeDragCoef_MidBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeDragCoef(1.00);
		// verify
		assert(value == MapReader().linearInterpolation(1.00, 0.4258, 1.020, 0.4335, 1.00));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeDragCoef_UpperBound
	* Test Force::computeDragCoef(speed) when speed
	* is equal to the max key in the map.
	*****************************************************/
	void TestComputeDragCoef_UpperBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeDragCoef(5.000);
		// verify
		assert(value == MapReader().linearInterpolation(2.890, 0.2306, 5.000, 0.2656, 5.000));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeAirDnsty_LowBound
	* Test Force::computeAirDensity(altitude) when 
	* altitude is equal to the min key in the map.
	*****************************************************/
	void TestComputeAirDnsty_LowBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeAirDensity(0);
		// verify
		assert(value == 1.2250000);
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeAirDnsty_MidVal
	* Test Force::computeAirDensity(altitude) when
	* altitude is between two keys in the map.
	*****************************************************/
	void TestComputeAirDnsty_MidVal() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeAirDensity(8503);
		// verify
		assert(value == MapReader().linearInterpolation(8000, 0.5258000, 9000, 0.4671000, 8503));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeAirDnsty_MidBound
	* Test Force::computeAirDensity(altitude) when
	* altitude is eqaul to a key within the map.
	*****************************************************/
	void TestComputeAirDnsty_MidBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeAirDensity(10000);
		// verify
		assert(value == MapReader().linearInterpolation(10000, 0.4135000, 15000, 0.1948000, 10000));
		// teardown
		delete force;
	}

	/****************************************************
	* TestComputeAirDnsty_UpperBound
	* Test Force::computeAirDensity(altitude) when
	* altitude is equal to the max key in the map.
	*****************************************************/
	void TestComputeAirDnsty_UpperBound() const {
		// setup
		Force* force = new Force();
		// exercise
		double value = force->computeAirDensity(80000);
		// verify
		assert(value == MapReader().linearInterpolation(70000, 0.0000828, 80000, 0.0000185, 80000));
		// teardown
		delete force;
	}
};
#endif // NDEBUG