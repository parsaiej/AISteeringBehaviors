#pragma once
#include "Steering.h"

class KinematicUnit;

class DynamicVelocityMatch : public Steering
{
public:
	DynamicVelocityMatch(KinematicUnit* pMover, KinematicUnit* pTarget, float targetRadius = 0.2f);
	~DynamicVelocityMatch() {};

	virtual Steering* getSteering();
protected:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	float mTargetRadius, mSlowRadius, mTimeToTarget;
};