#include "DynamicPursueSteering.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"

DynamicPursueSteering::DynamicPursueSteering(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldEvade)
:DynamicSeekSteering(pMover, nullptr, shouldEvade)
, mpMover(pMover)
, mpTarget(pTarget)
{
	mApplyDirectly = false;
}

Steering* DynamicPursueSteering::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();
	float distance = direction.getLength();

	float speed = mpMover->getVelocity().getLength();

	float prediction;
	if (speed <= distance / 20.0f)
		prediction = 20.0f;
	else
		prediction = distance / speed;

	//GNULLKINEMATICUNIT??? 
	KinematicUnit temp(gpGame->getSpriteManager()->getSprite(2), "NULL", this->mpTarget->getPosition(), 0.0f, gZeroVector2D, 0.0f);
	temp.setPosition(temp.getPosition() + (this->mpTarget->getVelocity() * prediction));
	DynamicSeekSteering::mpTarget = &temp;

	return DynamicSeekSteering::getSteering();
}