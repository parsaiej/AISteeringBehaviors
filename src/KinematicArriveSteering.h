#pragma once

#include "Steering.h"

class KinematicUnit;

class KinematicArriveSteering:public Steering
{
public:
	KinematicArriveSteering( KinematicUnit* pMover, const Vector2D& targetPosition, float satisfactionRadius = 1.0f, float timeToTarget = 0.25f );
	~KinematicArriveSteering(){};

	void setTarget( const Vector2D& targetPosition ){ mTarget = targetPosition; };

	virtual Steering* getSteering();

private:
	Vector2D mTarget;
	KinematicUnit* mpMover;
	float mSatisfactionRadius;
	float mTimeToTarget;
};