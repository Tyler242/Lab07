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
#include "Constants.cpp"


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
	projectileActive = false;
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

	projectileActive = false;
}


/********************************************************
 * RELOAD
 * Resets the projectile and trajectory 
 ********************************************************/
void Simulator::reload()
{
	howitzer.reload();
	trajectory.reset();
	projectileActive = false;
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

	if (projectileActive) run();

	// fire
	if (pUI->isSpace())
		if (howitzer.canFire()) {
			
			howitzer.fireProjectile();
			hangTime = 0.0;

			projectile = Projectile(ptHowitzer, howitzerAngle);
			projectile.move();
			trajectory.addProjectile(projectile);
			projectileActive = true;
		}
}


/********************************************************
 * RUN
 * Update each frame with the input from the user.
 ********************************************************/
void Simulator::run()
{
	if (projectile.isFlying(ground)) {
		hangTime += TIME_INTERVAL;
		projectile.move();
		trajectory.addProjectile(projectile);
	}
	else {
		projectileActive = false;
		// did the projectile land on the target
		Position target = ground.getTarget();
		Position projPos = projectile.getPos();

		if (target.getMetersX() == projPos.getMetersX() &&
			target.getMetersY() == projPos.getMetersY()) {
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