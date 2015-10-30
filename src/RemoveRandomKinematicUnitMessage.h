#pragma once

#include "GameMessage.h"
#include "KinematicUnitManager.h"

class RemoveRandomKinematicUnitMessage :public GameMessage
{
public:
	RemoveRandomKinematicUnitMessage();
	~RemoveRandomKinematicUnitMessage();

	void process();
};