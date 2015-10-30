#pragma once
#include "GameMessage.h"

class CoordinatesFollowMouseMessage : public GameMessage
{
public:
	CoordinatesFollowMouseMessage(ALLEGRO_MOUSE_STATE);
	~CoordinatesFollowMouseMessage();

	void process();
private:
	ALLEGRO_MOUSE_STATE mMouseState;
};