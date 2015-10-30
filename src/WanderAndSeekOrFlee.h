#pragma once

#pragma once

#include "Steering.h"

class KinematicUnit;
class DynamicWanderSteering;
class DynamicSeekSteering;

class WanderAndSeekOrFlee : public Steering
{
public:
	WanderAndSeekOrFlee(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, float radius);
	~WanderAndSeekOrFlee();

	virtual Steering* getSteering();
private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;

	DynamicWanderSteering* mpDynamicWanderSteering;
	DynamicSeekSteering* mpDynamicSeekSteering;

	float mRadius;
	bool mShouldFlee;
};