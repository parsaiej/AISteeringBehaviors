#pragma once

#include "DynamicSeekSteering.h"

class KinematicUnit;

class DynamicPursueSteering : public DynamicSeekSteering
{
public:
	DynamicPursueSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldEvade = false);
	~DynamicPursueSteering() {};

	void setTarget(KinematicUnit* pTarget){ mpTarget = pTarget; };

	virtual Steering* getSteering();
private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
};