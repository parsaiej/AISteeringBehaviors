#include "DynamicGroupAlignSteering.h"
#include "SpriteManager.h"
#include "KinematicUnit.h"

DynamicGroupAlignSteering::DynamicGroupAlignSteering(KinematicUnit* pMover, float radius)
	:DynamicAlignSteering(pMover, nullptr)
	,mpMover(pMover)
	, mRadius(radius)
{
	mApplyDirectly = false;
}

Steering* DynamicGroupAlignSteering::getSteering()
{
	float orientation = 0;
	int neighbors = 0;
	for (size_t i = 0; i < UNIT_MANAGER->m_units.size(); i++)
	{
		KinematicUnit *temp = UNIT_MANAGER->m_units[i];
		Vector2D direction = mpMover->getPosition() - temp->getPosition();
		float distance = direction.getLength();

		if (distance < mRadius)
		{
			orientation += temp->getOrientation();
			neighbors++;
		}
	}

	if (neighbors == 0)
		return this;

	orientation /= neighbors;

	KinematicUnit temp(gpGame->getSpriteManager()->getSprite(2), "NULL", gZeroVector2D, orientation, gZeroVector2D, 0.0f);
	mpTarget = &temp;

	return DynamicAlignSteering::getSteering();
}