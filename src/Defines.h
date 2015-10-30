#pragma once

#include <string>

typedef int IDType;
typedef std::string IDDescriptor;

const IDType INVALID_ID = -1;

const IDType HIGHEST_ID = 9999;

#define MESSAGE_MANAGER gpGame->getMessageManager()
#define GRAPHICS_SYSTEM gpGame->getGraphicsSystem()
#define UNIT_MANAGER gpGame->getKinematicUnitManager()