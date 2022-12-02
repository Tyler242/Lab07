/***********************************************************************
 * Header File:
 *    Simulator.h
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    The implemenation for the Simulator class, which runs the Howitzer
 *	  simulation
 ************************************************************************/

#pragma once

#include "ground.h"		// ground
#include "position.h"	// for position Point
#include "Trajectory.h"
#include "Projectile.h"
#include "Howitzer.h"
#include "uiInteract.h"	// interact
#include "uiDraw.h"		// for gout


/*****************************************************
 * SIMULATOR
 * The Simulator class
 *****************************************************/
class Simulator
{
public:
	// Constructor
	Simulator(const Position& ptUpperRight);
	
	// resets the simulator components
	void reset();

	// handles user input
	void input(const Interface* pUI);

	// runs the simulator
	void run(const Interface* pUI);

	// draws all components
	void draw();

private:
	Ground ground;
	Trajectory trajectory;
	Projectile projectile;
	Howitzer howitzer;
	Position ptHowitzer;
	Position ptUpperRight;
	double howitzerAngle;	// angle of the howitzer barrel
	double time;			// amount of time since the last firing in seconds
};

