#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "KinematicUnitManager.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	UNIT_MANAGER->getKinematicUnit("player")->arrive(mPos);
}