#pragma once

#include "Steering.h"

class KinematicUnit;

class DynamicSeparationSteering : public Steering
{
public:
	DynamicSeparationSteering(KinematicUnit* pMover, float threshold = 300.0f, float decayCoefficient = 100.0f);
	~DynamicSeparationSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	float mThreshold,
		mDecayCoefficient;
};