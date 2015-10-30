#include "DynamicWanderSteering.h"
#include "KinematicUnit.h"
#include "Steering.h"
#include "Game.h"
#include "SpriteManager.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

DynamicWanderSteering::DynamicWanderSteering(KinematicUnit* pMover, float wanderOffset, float wanderRadius, float wanderRate, float wanderOrientation, float targetRadius, float slowRadius, float timeToTarget)
	: DynamicFaceSteering(pMover, nullptr, targetRadius, slowRadius, timeToTarget)
	, mpMover(pMover)
	, mWanderOffset(wanderOffset)
	, mWanderRadius(wanderRadius)
	, mWanderRate(wanderRate)
	, mWanderOrientation(wanderOrientation)
{
	mApplyDirectly = false;
	mFrameCount = 0;
}

Steering* DynamicWanderSteering::getSteering()
{
	mWanderOrientation += genRandomBinomial() * mWanderRate;

	float targetOrientation = mWanderOrientation + mpMover->getOrientation();

	Vector2D target = mpMover->getPosition() + (mpMover->getOrientationAsVector() * mWanderOffset);

	//Just holding on to this for when I draw my circle.
	Vector2D circlePos = target;

	Vector2D targetOffset = (asVector(targetOrientation) * mWanderRadius);
	target = target + targetOffset;

	//I needed to set up faux kunits that the mover could point to.
	//Simply Having a new kinematic unit = *this->mpTarget causes issues
	//when deleting the faux units steering.
	KinematicUnit temp(gpGame->getSpriteManager()->getSprite(2), "NULL", target, targetOrientation, gZeroVector2D, 0.0f);
	mpTarget = &temp;

	//Steering *steering = DynamicFaceSteering::getSteering();
	//Vector2D line(mpMover->getPosition() - mpTarget->getPosition());
	//line.normalize();
	//line *= mpMover->getMaxAcceleration();
	//steering->setLinear(line);//mpMover->getOrientationAsVector() * mpMover->getMaxAcceleration());


	//Temporary Hack. This part doesn't follow the book, but works well enough
	//to create a wander-like behavior.
	mLinear = mpMover->getPosition() - mpTarget->getPosition();
	mLinear.normalize();
	mLinear *= mpMover->getMaxAcceleration();

	//Give graphical feedback of what's happening.

	if (debugOn)
	{
		al_draw_line(mpMover->getPosition().getX(), mpMover->getPosition().getY(), mpTarget->getPosition().getX(), mpTarget->getPosition().getY(), al_map_rgb(0, 0, 0), 2.0f);
		al_draw_circle(circlePos.getX(), circlePos.getY(), mWanderRadius, al_map_rgb(0, 0, 0), 1.0f);
	}

	return DynamicFaceSteering::getSteering();
}