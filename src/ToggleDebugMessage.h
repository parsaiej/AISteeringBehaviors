#pragma once
#include "GameMessage.h"

class ToggleDebugMessage : public GameMessage
{
public:
	ToggleDebugMessage();
	~ToggleDebugMessage() {};

	void process();
private:
};