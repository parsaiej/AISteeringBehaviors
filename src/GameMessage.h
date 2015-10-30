#pragma once

#include "Trackable.h"
#include "Game.h"
#include "GameMessageManager.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	EXIT_GAME_MESSAGE = 0,
	PLAYER_MOVETO_MESSAGE = 1,
	ADD_KINEMATIC_UNIT = 2,
	REMOVE_RANDOM_KINEMATIC_UNIT = 3,
	COORDINATES_FOLLOW_MOUSE = 4,
	DEBUG_ON = 5,
	MODIFY_FLOCKING_WEIGHT = 6
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

