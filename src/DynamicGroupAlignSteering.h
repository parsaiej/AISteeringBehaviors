#pragma once

#include "DynamicAlignSteering.h"

class KinematicUnit;

class DynamicGroupAlignSteering : public DynamicAlignSteering
{
public:
	DynamicGroupAlignSteering(KinematicUnit* pMover, float = 300.0f);
	~DynamicGroupAlignSteering() {};

	virtual Steering* getSteering();
protected:
	KinematicUnit* mpMover;
	float mRadius;
};