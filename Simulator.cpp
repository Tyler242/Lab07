/***********************************************************************
 * Source File:
 *    Simulator : runs the Howitzer simulation
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    Manages the components and their iteractions for the lHowtizer 
 *	  simulation.
 ************************************************************************/

#include "Simulator.h"


/********************************************************
 * SIMULATOR constructor
 * Creates a new instance of Simulator
 ********************************************************/
Simulator::Simulator(const Position& ptUpperRight) : 
	ptUpperRight(ptUpperRight), ground(ptUpperRight), trajectory()
{
	howitzerAngle = 0.0;
	hangTime = 0.0;

	// Set howitzer position
	ptHowitzer.setPixelsX(1 + (rand() % int(ptUpperRight.getPixelsX())));		// Set X, radnome

	ground.reset(ptHowitzer);		// Set Y

	howitzer = Howitzer(ptHowitzer);
}


/********************************************************
 * RESET
 * Resets the simulator by calling reset methods for 
 * member objects
 ********************************************************/
void Simulator::reset()
{
	howitzerAngle = 0.0;
	
	// Set new howitzer position
	ptHowitzer.setPixelsX(1 + (rand() % int(ptUpperRight.getPixelsX())));		// Set X, radnome

	ground.reset(ptHowitzer);		// Set Y
	
	howitzer.reset(ptHowitzer);

	trajectory.reset();
}


/********************************************************
 * RELOAD
 * Resets the projectile and trajectory 
 ********************************************************/
void Simulator::reload()
{
	howitzer.reload();
	trajectory.reset();
}


/********************************************************
 * INPUT
 * Handle input from the user to move or fire the howitzer
 ********************************************************/
void Simulator::input(const Interface* pUI)
{
	// move a lot
	if (pUI->isRight())
		howitzerAngle += 0.05;
	if (pUI->isLeft())
		howitzerAngle -= 0.05;

	// move a little
	if (pUI->isUp())
		howitzerAngle += (howitzerAngle >= 0 ? -0.003 : 0.003);
	if (pUI->isDown())
		howitzerAngle += (howitzerAngle >= 0 ? 0.003 : -0.003);

	// fire 
	if (pUI->isSpace())
		if (howitzer.canFire()) {
			howitzer.fireProjectile();
			hangTime = 0.0;
			projectile = Projectile(ptHowitzer, howitzerAngle);
		}
}


/********************************************************
 * RUN
 * Update each frame with the input from the user.
 ********************************************************/
void Simulator::run(const Interface* pUI)
{
	if (howitzer.canFire() == true) {
		input(pUI);
	}

	else if (!projectile.isFlying()) {
		if (projectile.isLandedOnTarget()) {
			reset();
		}

		// Reset projectile and trajectory
		else {
			reload();
		}
	}
}


/********************************************************
 * DRAW
 * Draws each component to the screen.
 ********************************************************/
void Simulator::draw()
{
	ogstream gout;

	ground.draw(gout);
	howitzer.draw(gout, howitzerAngle, hangTime);
	trajectory.draw(gout);
}

