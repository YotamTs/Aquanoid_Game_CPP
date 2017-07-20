#include "Brick.h"
#include "Controller.h"

//-=-----------------------------------------Brick.cpp----------------------------------------=-//
void Brick::destroy(Controller& con)
{
	_destroyed = true;
	con.oneBrickReduced();
}
//----------------------------------------------
void Brick::collide(const GameObject* gameObjectP , Controller& con)
{
	play_sound();
	destroy(con);
	Ball *ballP = (Ball*) gameObjectP;
	ballUpdate(ballP);
	con.scoreUpdate(10);
}
//----------------------------------------------
void Brick::play_sound()
{
	_sound.play();
}
//----------------------------------------------
void Brick::draw() const
{
	_win.draw(_sprite);
};
//----------------------------------------------
//Update ball direction:
void Brick::ballUpdate(Ball *ballP)
{
	//Calculate how much the ball intersects the brick in every direction.
	float overlapLeft = ballP->getRight() - getLeft();
	float overlapRight = getRight() - ballP->getLeft();
	float overlapTop = ballP->getBottom() - getTop();
	float overlapBottom =  getBottom() - ballP->getTop();

	//If the size of the left overlap is smaller than the right
	//overlap - the ball hit the brick from the left.
	bool ballFromLeft( abs(overlapLeft) < abs(overlapRight));

	//If the size of the top overlap is smaller than the bottom
	//overlap - the ball hit the brick from the top.
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	//Store the minimum overlaps for the X and Y axis.
	float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
	float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

	//Change the X or Y velocity to create a "realistic" response for the collision.
	if( abs(minOverlapX) < abs(minOverlapY) )
	{
		ballP->setDirectionX(ballFromLeft ? -ballP->getVelocity() : ballP->getVelocity());
	}
	else
	{
		ballP->setDirectionY(ballFromTop ? -ballP->getVelocity() : ballP->getVelocity());
	}
}