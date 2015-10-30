#pragma once
#include "GameMessage.h"
#include "KinematicUnitManager.h"
#include "Vector2D.h"

class AddKinematicUnit : public GameMessage
{
public:
	AddKinematicUnit(const SteeringType &steertype, int num_to_spawn);
	~AddKinematicUnit() {};

	inline SteeringType getSteerType() const { return mSteerType; };

	void process();
private:
	SteeringType mSteerType;
	int mNumToSpawn;
};