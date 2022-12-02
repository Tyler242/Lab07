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
	Howitzer(const Position& ptHowitzer);

	Position getPosition() const;

	void addAngle(const double angle);
	double getAngle() const;

	bool canFire() const;
	void fireProjectile();

	void reload();
	void reset(const Position& ptHowitzer);
	void draw(ogstream& gout, const double angle) const;

private:
	Position position;	// location of the howitzer on the screen
	bool canShoot;		// if the howitzer can fire a round
};

