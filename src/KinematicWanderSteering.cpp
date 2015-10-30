#include "KinematicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover)
:mpMover(pMover)
{
	mApplyDirectly = false;
}

Steering* KinematicWanderSteering::getSteering()
{
	mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
	mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);

	return this;
}