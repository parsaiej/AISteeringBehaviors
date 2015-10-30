#include "ToggleDebugMessage.h"

ToggleDebugMessage::ToggleDebugMessage()
	:GameMessage(DEBUG_ON)
{
}

void ToggleDebugMessage::process()
{
	(debugOn) ? (debugOn = false) : (debugOn = true);
}