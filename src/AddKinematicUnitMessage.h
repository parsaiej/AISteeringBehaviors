#pragma once
#include "GameMessage.h"

enum SteeringType
{
	INVALID_STEERTYPE = -1,
	SEEK,
	ARRIVE,
	FLEE,
	WANDER,
	NUM_STEERTYPES
};

class AddKinematicUnitMessage : public GameMessage
{
public:
	AddKinematicUnitMessage(const SteeringType &steertype);
	~AddKinematicUnitMessage();

	inline SteeringType getSteerType() const { return mSteerType; };

	void process();
private:
	SteeringType mSteerType;
};