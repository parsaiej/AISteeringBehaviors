#pragma once

#include <allegro5\allegro.h>

#include "Trackable.h"
#include "Game.h"
#include "ExitGameMessage.h"
#include "AddKinematicUnitNearPlayerMessage.h"
#include "AddKinematicUnit.h"
#include "RemoveRandomKinematicUnitMessage.h"
#include "CoordinatesFollowMouseMessage.h"
#include "PlayerMoveToMessage.h"
#include "GraphicsSystem.h"
#include "GameMessageManager.h"
#include "ToggleDebugMessage.h"
#include "ModifyFlockingWeightMessage.h"

enum
{
	MOUSE_LEFT_BUTTON = 1,
	MOUSE_RIGHT_BUTTON = 2,
	MOUSE_MIDDLE_BUTTON = 3
};

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();
	
	void init();
	void update();

	bool isMouseButtonDown(int);
	bool isKeyboardKeyDown(int);
private:
	ALLEGRO_EVENT_QUEUE *mp_eventque;
};