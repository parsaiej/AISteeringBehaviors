#include "AddKinematicUnitMessage.h"

#include "Game.h"
#include "KinematicUnit.h"
#include "KinematicUnitManager.h"
#include "SpriteManager.h"

AddKinematicUnitMessage::AddKinematicUnitMessage(const SteeringType &steertype)
	:GameMessage(ADD_KINEMATIC_UNIT)
	, mSteerType(steertype)
{
}

AddKinematicUnitMessage::~AddKinematicUnitMessage()
{
}

void AddKinematicUnitMessage::process()
{
	std::cout << "Message: AddKinematicUnitMessage\n";

	Vector2D pos(100.0f, 100.0f);
	Vector2D vel(0.0f, 0.0f);

	KinematicUnit *temp = new KinematicUnit(gpGame->getSpriteManager()->getSprite(2), "SpawnAI", pos, 1, vel, 0.0f, 180.0f, 100.0f);

	switch (mSteerType)
	{
	case 0:
		temp->dynamicSeek(UNIT_MANAGER->getKinematicUnit("player"));
		break;
	case 1:
		temp->dynamicArrive(UNIT_MANAGER->getKinematicUnit("player"));
		break;
	case 2:
		temp->dynamicFlee(UNIT_MANAGER->getKinematicUnit("player"));
		break;
	case 3:
		temp->wander();
		break;
	}

	UNIT_MANAGER->addKinematicUnit(temp);
}