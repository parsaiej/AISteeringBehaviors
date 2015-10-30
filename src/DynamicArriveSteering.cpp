#include "DynamicArriveSteering.h"
#include "KinematicUnit.h"

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

DynamicArriveSteering::DynamicArriveSteering(KinematicUnit *pMover, KinematicUnit* pTarget, float targetRadius, float slowRadius, float timeToTarget)
:mpMover(pMover)
,mpTarget(pTarget)
,mTargetRadius(targetRadius)
,mSlowRadius(slowRadius)
,mTimeToTarget(timeToTarget)
{
	mApplyDirectly = true;
}

Steering* DynamicArriveSteering::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();
	float distance = direction.getLength();

	//are we there?
	if( distance < mTargetRadius )
	{
		mLinear = gZeroVector2D;
		mAngular = 0.0f;

		return this;
	}

	float targetSpeed = 0.0f;

	//are we outside slow radius?
	if( distance > mSlowRadius )
	{
		targetSpeed = mpMover->getMaxVelocity();
	}
	else
	{
		targetSpeed = ( mpMover->getMaxVelocity() * distance ) / mSlowRadius;
	}

	//combine speed and direction to get targetVelocity
	Vector2D targetVelocity = direction;

	//######################## For some reason not normalizing the targetVelocity fixes all of the orientation issues for the Dynamic Arrival steering... #############################
	targetVelocity.normalize(); 

	targetVelocity *= targetSpeed;

	//set acceleration
	mLinear = targetVelocity - mpMover->getVelocity();
	mLinear /= mTimeToTarget;

	//check if too fast
	if( mLinear.getLength() > mpMover->getMaxAcceleration() )
	{
		//cut down to max
		mLinear.normalize();
		mLinear *= mpMover->getMaxAcceleration();
	}

	if (debugOn)
		al_draw_line(mpMover->getPosition().getX(), mpMover->getPosition().getY(), mpTarget->getPosition().getX(), mpTarget->getPosition().getY(), al_map_rgb(0, 0, 0), 2.0f);

	mAngular = 0.0f;

	return this;
}