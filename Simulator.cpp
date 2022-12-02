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
	time = 0.0;

	// Set howitzer position
	ptHowitzer.setPixelsX(1 + (rand() % int(ptUpperRight.getPixelsX())));		// Set X, radnome

	ground.reset(ptHowitzer);		// Set Y

	howitzer = Howitzer(ptHowitzer);

	// Project position
	projectile = Projectile(angle, ptHowitzer);

}


/********************************************************
 * RESET
 * Resets the simulator by calling reset methods for 
 * member objects
 ********************************************************/
void Simulator::reset()
{
	howitzerAngle = 0.0;
	time = 0.0;
	
	// Set new howitzer position
	ptHowitzer.setPixelsX(1 + (rand() % int(ptUpperRight.getPixelsX())));		// Set X, radnome

	ground.reset(ptHowitzer);		// Set Y
	
	howitzer.reset(ptHowitzer);

	trajectory.reset();

	projectile = Projectile(howitzerAngle, ptHowitzer);
}


/********************************************************
 * INPUT
 * Handle input from the user to move or fire the howitzer
 * 
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
			time = 0.0;
		}
}


/********************************************************
 * RUN
 * Update each frame with the input from the user.
 ********************************************************/
void Simulator::run(const Interface* pUI)
{
	
}


/********************************************************
 * DRAW
 * Draws each component to the screen.
 ********************************************************/
void Simulator::draw()
{
	ogstream gout;

	ground.draw(gout);
	howitzer.draw(gout, howitzerAngle);
}

