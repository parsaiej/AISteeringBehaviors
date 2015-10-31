#include "DynamicAlignSteering.h"
#include "KinematicUnit.h"

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

DynamicAlignSteering::DynamicAlignSteering(KinematicUnit* pMover, KinematicUnit* pTarget, float targetRadius, float slowRadius, float timeToTarget)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mTargetRadius(targetRadius)
	, mSlowRadius(slowRadius)
	, mTimeToTarget(timeToTarget)
{
	mApplyDirectly = false;
}

Steering* DynamicAlignSteering::getSteering()
{
	float rotation = mpTarget->getOrientation() - mpMover->getOrientation();
	rotation = mapToRange(rotation);
	float rotationSize = abs(rotation);

	if (rotationSize < mTargetRadius)
	{
		mAngular = 0.0f;
		mpMover->setRotationalVelocity(0.0f);
		return this;
	}

	float targetRotation = 0.0f;
	if (rotationSize > mSlowRadius)
		targetRotation = mpMover->getMaxRotation();
	else
		targetRotation = mpMover->getMaxRotation() * rotationSize / mSlowRadius;

	targetRotation *= rotation / rotationSize;

	mAngular = targetRotation - mpMover->getOrientation();

	if (((targetRotation > 0) && (mAngular < 0)) || ((targetRotation < 0) && (mAngular > 0)))
	{
		mAngular *= -1;
	}

	mAngular /= mTimeToTarget;

	float angularAcceleration = abs(mAngular);
	if (angularAcceleration > mpMover->getMaxRotationalVelocity())
	{
		mAngular /= angularAcceleration;
		mAngular *= mpMover->getMaxRotationalVelocity();
	}

	mLinear = gZeroVector2D;

	return this;
}
