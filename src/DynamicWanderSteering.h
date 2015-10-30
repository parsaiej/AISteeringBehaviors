#pragma once

#include "DynamicFaceSteering.h"

class KinematicUnit;

class DynamicWanderSteering : public DynamicFaceSteering
{
public:
	//DynamicWanderSteering(KinematicUnit* pMover, float wanderOffset = 50.0f, float wanderRadius = 80.0f, float wanderRate = 0.5f, float wanderOrientation = 10.0f, float targetRadius = 5.0f, float slowRadius = 10.0f, float timeToTarget = 5.0f);
	DynamicWanderSteering(KinematicUnit* pMover, float wanderOffset = 0.0f, float wanderRadius = 80.0f, float wanderRate = 0.5f, float wanderOrientation = 10.0f, float targetRadius = 5.0f, float slowRadius = 10.0f, float timeToTarget = 5.0f);
	~DynamicWanderSteering() {};

	virtual Steering* getSteering();

	inline Vector2D asVector(float orientation){ return Vector2D(sinf(orientation), cosf(orientation)); };
private:
	KinematicUnit* mpMover;
	float mWanderOffset,
		mWanderRadius,
		mWanderRate,
		mWanderOrientation;

	int mFrameCount;
};