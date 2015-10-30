#include "AddKinematicUnit.h"
#include "SpriteManager.h"

AddKinematicUnit::AddKinematicUnit(const SteeringType& steertype, int num_to_spawn)
	:GameMessage(ADD_KINEMATIC_UNIT)
	, mSteerType(steertype)
	, mNumToSpawn(num_to_spawn)
{
}

void AddKinematicUnit::process()
{
	for (int i = 0; i < mNumToSpawn; i++)
	{
		int randX = rand() % GRAPHICS_SYSTEM->getWidth();
		int randY = rand() % GRAPHICS_SYSTEM->getHeight();

		KinematicUnit *temp = new KinematicUnit(gpGame->getSpriteManager()->getSprite(2), mTypeArray[mSteerType] + "AI", Vector2D(randX, randY), 1.0f, Vector2D(100, 100), 1.0f, 180.0f, 250.0f);

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
			temp->dynamicWander();
			break;
		case 4:
			temp->dynamicAlign(UNIT_MANAGER->getKinematicUnit("player"));
			break;
		case 5:
			temp->dynamicPursue(UNIT_MANAGER->getKinematicUnit("player"));
			break;
		case 6:
			temp->dynamicFace(UNIT_MANAGER->getKinematicUnit("player"));
			break;
		case 7:
			temp->dynamicWanderAndSeek(UNIT_MANAGER->getKinematicUnit("player"), 100);
			break;
		case 8:
			temp->dynamicWanderAndFlee(UNIT_MANAGER->getKinematicUnit("player"), 100);
			break;
		case 9:
			temp->dynamicSeparation();
			break;
		case 10:
			temp->dynamicCohesion();
			break;
		case 11:
			temp->dynamicFlocking();
			break;
		case 12:
			temp->dynamicVelocityMatch(UNIT_MANAGER->getKinematicUnit("player"));
			break;
		}

		UNIT_MANAGER->addKinematicUnit(temp);
	}
}