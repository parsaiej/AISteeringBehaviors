#pragma once

#include "DynamicAlignSteering.h"

class KinematicUnit;

class DynamicFaceSteering : public DynamicAlignSteering
{
public:
	DynamicFaceSteering(KinematicUnit* pMover, KinematicUnit* pTarget, float targetRadius = 0.2f, float slowRadius = 2.5f, float timeToTarget = 0.15f);
	~DynamicFaceSteering() {};

	void setTarget(KinematicUnit* pTarget){ mpTarget = pTarget; };

	virtual Steering* getSteering();
protected:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
};