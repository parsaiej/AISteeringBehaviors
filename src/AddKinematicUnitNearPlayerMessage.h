#pragma once
#include "GameMessage.h"
#include "KinematicUnitManager.h"
#include "Vector2D.h"

class AddKinematicUnitNearPlayerMessage : public GameMessage
{
public:
	AddKinematicUnitNearPlayerMessage(const SteeringType &steertype, int radius);
	~AddKinematicUnitNearPlayerMessage() {};

	inline SteeringType getSteerType() const { return mSteerType; };

	void process();
private:
	SteeringType mSteerType;
	int mRadius;
};