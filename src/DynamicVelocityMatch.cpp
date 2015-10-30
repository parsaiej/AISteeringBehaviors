#include "DynamicVelocityMatch.h"
#include "KinematicUnit.h"

DynamicVelocityMatch::DynamicVelocityMatch(KinematicUnit* pMover, KinematicUnit* pTarget, float timeToTarget)
:mpMover(pMover)
, mpTarget(pTarget)
, mTimeToTarget(timeToTarget)
{
	mApplyDirectly = false;
}

Steering* DynamicVelocityMatch::getSteering()
{
	mLinear = mpTarget->getVelocity() - mpMover->getVelocity();
	mLinear /= mTimeToTarget;

	if (mLinear.getLength() > mpMover->getMaxAcceleration())
	{
		mLinear.normalize();
		mLinear *= mpMover->getMaxAcceleration();
	}

	mAngular = 0;
	return this;
}