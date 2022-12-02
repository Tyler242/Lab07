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
Howitzer::Howitzer(const Position& ptHowitzer) :
	position(ptHowitzer)
{
	time = 0.0;
	canShoot = true;
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
void Howitzer::reset(const Position& ptHowitzer)
{
	time = 0.0;
	canShoot = true;

	position = ptHowitzer;
}


/*****************************************************
 * GET POSITION
 * Returns the current position of the Howitzer
 *****************************************************/
void Howitzer::draw(ogstream& gout, const double angle) const
{
	gout.drawHowitzer(position, angle, time);
}
