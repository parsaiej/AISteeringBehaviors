#include "RemoveRandomKinematicUnitMessage.h"

RemoveRandomKinematicUnitMessage::RemoveRandomKinematicUnitMessage()
	:GameMessage(REMOVE_RANDOM_KINEMATIC_UNIT)
{
}

RemoveRandomKinematicUnitMessage::~RemoveRandomKinematicUnitMessage()
{
}

void RemoveRandomKinematicUnitMessage::process()
{
	UNIT_MANAGER->removeRandomKinematicUnit();
}