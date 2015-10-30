#include "AddKinematicUnitNearPlayerMessage.h"

#include "Game.h"
#include "KinematicUnit.h"
#include "KinematicUnitManager.h"
#include "SpriteManager.h"

AddKinematicUnitNearPlayerMessage::AddKinematicUnitNearPlayerMessage(const SteeringType &steertype, int radius)
	:GameMessage(ADD_KINEMATIC_UNIT)
	, mSteerType(steertype)
	, mRadius(radius)
{
}

void AddKinematicUnitNearPlayerMessage::process()
{
	Vector2D vel(0.0f, 0.0f);

	int theta = (rand() % 360);
	int opp = sin(theta) * mRadius;
	int adj = cos(theta) * mRadius;

	Vector2D playerVector = UNIT_MANAGER->getKinematicUnit("player")->getPosition();
	Vector2D spawnPos = Vector2D((playerVector.getX() + adj) + mRadius, (playerVector.getY() + opp) + mRadius);

	spawnPos.setX(spawnPos.getX() - (playerVector.getX() / 2));
	spawnPos.setY(spawnPos.getY() - (playerVector.getY() / 2));

	/* Distance confirmation (It's close enough).
	int x_dist = abs(playerVector.getX() - spawnPos.getX());
	int y_dist = abs(playerVector.getY() - spawnPos.getY());
	std::cout << sqrt((x_dist * x_dist) + (y_dist * y_dist)) << std::endl;
	*/

	KinematicUnit *temp = new KinematicUnit(gpGame->getSpriteManager()->getSprite(2), mTypeArray[mSteerType] + "AI", spawnPos, 1.0f, vel, 1.0f, 180.0f, 200.0f);

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