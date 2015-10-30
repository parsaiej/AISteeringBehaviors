#pragma once

#include "Steering.h"

class KinematicUnit;

class DynamicSeekSteering:public Steering
{
public:
	DynamicSeekSteering( KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false );
	~DynamicSeekSteering(){};

	void setTarget( KinematicUnit* pTarget ){ mpTarget = pTarget; };

	virtual Steering* getSteering();

protected:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;
};