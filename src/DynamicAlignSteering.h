#pragma once

#include "Steering.h"

class KinematicUnit;

class DynamicAlignSteering : public Steering
{
public:
	DynamicAlignSteering(KinematicUnit* pMover, KinematicUnit* pTarget, float targetRadius = 0.2f, float slowRadius = 2.5f, float timeToTarget = 0.15f);
	~DynamicAlignSteering() {};

	void setTarget(KinematicUnit* pTarget){ mpTarget = pTarget; };

	virtual Steering* getSteering();
protected:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	float mTargetRadius, mSlowRadius, mTimeToTarget;
};