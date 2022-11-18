/***********************************************************************
 * Source File:
 *    Howitzer.cpp
 * Author:
 *    Caleb Rasmussen & Tyler Shellman
 * Summary:
 *    The implemenation for the Howitzer class methods
 ************************************************************************/


#include "Howitzer.h"


/*****************************************************
 * DEFAULT CONSTUCTOR
 * Creates a new instance of Howitzer
 *****************************************************/
Howitzer::Howitzer(const Position ptUpperRight) 
{
	angle = 0.0;
	time = 0.0;
	canShoot = true;
	
	// Generates random starting postion
	position.setPixelsX(1 + (rand() % int(ptUpperRight.getPixelsX())));
	position.setPixelsY(0.0);
}


/*****************************************************
 * GET POSITION
 * Returns the current position of the Howitzer
 *****************************************************/
Position Howitzer::getPosition() const
{
	return position;
}


/*****************************************************
 * ADD ANGLE
 * Adds an angle to the current angle of the Howitzer
 *****************************************************/
void Howitzer::addAngle(const double angle)
{
	this->angle += angle;
}


/*****************************************************
 * GET ANGLE
 * Returns the current angle of the Howitzer barrel
 *****************************************************/
double Howitzer::getAngle() const
{
	return angle;
}


/*****************************************************
 * CAN FIRE
 * Returns whether the howitzer can fire or not
 *****************************************************/
bool Howitzer::canFire() const
{
	return canShoot;
}


/*****************************************************
 * FIRE PROJECTILE
 *
 *****************************************************/
void Howitzer::fireProjectile()
{
	canShoot = false;
	time = 0.0;
}


/*****************************************************
 * RELOAD
 * Reset canShoot to true
 *****************************************************/
void Howitzer::reload()
{
	canShoot = true;
}


/*****************************************************
 * GET POSITION
 * Resets the howitzer with new postion
 *****************************************************/
void Howitzer::reset(const Position ptUpperRight)
{
	angle = 0.0;
	time = 0.0;
	canShoot = true;

	// Generates random starting postion
	position.setPixelsX(1 + (rand() % int(ptUpperRight.getPixelsX())));
	position.setPixelsY(0.0);
}


/*****************************************************
 * GET POSITION
 * Returns the current position of the Howitzer
 *****************************************************/
void Howitzer::draw(ogstream& gout) const
{
	gout.drawHowitzer(position, angle, time);
}
