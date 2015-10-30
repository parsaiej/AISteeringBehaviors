#include "ModifyFlockingWeightMessage.h"

ModifyFlockingWeightMessage::ModifyFlockingWeightMessage(const WeightModifier &modifier, float weightMod)
	:GameMessage(MODIFY_FLOCKING_WEIGHT)
	, mModifier(modifier)
	, mWeightMod(weightMod)
{
}

void ModifyFlockingWeightMessage::process()
{
	DynamicFlockingSteering::modifyWeight(mModifier, mWeightMod);
}