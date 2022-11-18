/***********************************************************************
 * Header File:
 *    Howitzer.h
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    The implemenation for the Howitzer class, which represents the 
 *    Howitzer in the simulation.
 ************************************************************************/

#pragma once

#include "position.h"	// for position Point
#include "uiDraw.h"		// for gout

#include <cstdlib>		// for rand()
#include <iostream>
using namespace std;

/*****************************************************
 * HOWITZER
 * Howitzer class
 *****************************************************/
class Howitzer
{
public:
	// Constructor
	Howitzer(const Position ptUpperRight);

	Position getPosition() const;

	void addAngle(const double angle);
	double getAngle() const;

	bool canFire() const;
	void fireProjectile();

	void reload();
	void reset(const Position ptUpperRight);
	void draw(ogstream& gout) const;

private:
	Position position;	// location of the howitzer on the screen
	double angle;		// angle of the howitzer barrel
	double time;		// amount of time since the last firing in seconds
	bool canShoot;		// if the howitzer can fire a round
};

