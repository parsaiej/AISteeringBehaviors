#pragma once
#include "DynamicVelocityMatch.h"

class KinematicUnit;

class DynamicGroupVelocityMatch : public DynamicVelocityMatch
{
public:
	DynamicGroupVelocityMatch(KinematicUnit* pMover, float = 300.0f);
	~DynamicGroupVelocityMatch() {};

	virtual Steering* getSteering();
private:
	KinematicUnit* mpMover;
	float mRadius;
};