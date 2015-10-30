#pragma once

#include "Steering.h"

class KinematicUnit;

class KinematicSeekSteering:public Steering
{
public:
	KinematicSeekSteering( KinematicUnit* pMover, const Vector2D& targetPosition );
	~KinematicSeekSteering(){};

	void setTarget( const Vector2D& targetPosition ){ mTarget = targetPosition; };

	virtual Steering* getSteering();

private:
	Vector2D mTarget;
	KinematicUnit* mpMover;
};