#include "KinematicSeekSteering.h"
#include "KinematicUnit.h"

KinematicSeekSteering::KinematicSeekSteering(KinematicUnit *pMover, const Vector2D &targetPosition)
:mpMover(pMover)
,mTarget(targetPosition)
{
}

Steering* KinematicSeekSteering::getSteering()
{
	mLinear = mTarget - mpMover->getPosition();
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0.0f;
	return this;
}