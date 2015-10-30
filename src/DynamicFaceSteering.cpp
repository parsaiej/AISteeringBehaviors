#include "DynamicFaceSteering.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"

DynamicFaceSteering::DynamicFaceSteering(KinematicUnit* pMover, KinematicUnit* pTarget, float targetRadius, float slowRadius, float timeToTarget)
	:DynamicAlignSteering(pMover, nullptr, targetRadius, slowRadius, timeToTarget)
	, mpMover(pMover)
	, mpTarget(pTarget)
{
	mApplyDirectly = false;
}

Steering* DynamicFaceSteering::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();

	if (!direction.hasNonZeroLength())
		return this;

	//Setup faux target
	KinematicUnit temp(gpGame->getSpriteManager()->getSprite(2), "NULL", this->mpTarget->getPosition(), this->mpTarget->getOrientation(), gZeroVector2D, 0.0f);

	//##### direction.getY() because the images are upside down ######
	temp.setOrientation(atan2(direction.getX(), -direction.getY()));

	DynamicAlignSteering::mpTarget = &temp;
	return DynamicAlignSteering::getSteering();
}