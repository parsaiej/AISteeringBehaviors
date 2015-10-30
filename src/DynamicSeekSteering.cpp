#include "DynamicSeekSteering.h"
#include "KinematicUnit.h"

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

DynamicSeekSteering::DynamicSeekSteering(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee)
:mpMover(pMover)
,mpTarget(pTarget)
,mShouldFlee(shouldFlee)
{
	mApplyDirectly = false;
}

Steering* DynamicSeekSteering::getSteering()
{
	if( !mShouldFlee )
	{
		mLinear = mpTarget->getPosition() - mpMover->getPosition();
	}
	else
	{
		mLinear = mpMover->getPosition() - mpTarget->getPosition();
	}

	mLinear.normalize();
	mLinear *= mpMover->getMaxAcceleration();

	mAngular = 0;

	if (debugOn)
		al_draw_line(mpMover->getPosition().getX(), mpMover->getPosition().getY(), mpTarget->getPosition().getX(), mpTarget->getPosition().getY(), al_map_rgb(0, 0, 0), 2.0f);

	return this;
}