#pragma once

#include "Steering.h"

class KinematicUnit;

class DynamicArriveSteering:public Steering
{
public:
	DynamicArriveSteering( KinematicUnit* pMover, KinematicUnit* pTarget, float targetRadius = 1.0f, float slowRadius = 10.0f, float timeToTarget = 0.25f );
	~DynamicArriveSteering(){};

	void setTarget( KinematicUnit* pTarget ){ mpTarget = pTarget; };

	virtual Steering* getSteering();

protected:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	float mTargetRadius;
	float mSlowRadius;
	float mTimeToTarget;
};