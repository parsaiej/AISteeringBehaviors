#pragma once
#include "GameMessage.h"

class ExitGameMessage : public GameMessage
{
public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();
private:
};