#pragma once
#include "GameMessage.h"
#include "DynamicFlockingSteering.h"

class ModifyFlockingWeightMessage : public GameMessage
{
public:
	ModifyFlockingWeightMessage(const WeightModifier &, float);
	~ModifyFlockingWeightMessage() {};

	void process();
private:
	WeightModifier mModifier;
	float mWeightMod;
};