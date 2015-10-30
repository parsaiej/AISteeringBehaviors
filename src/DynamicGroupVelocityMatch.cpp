#include "DynamicGroupVelocityMatch.h"
#include "SpriteManager.h"
#include "KinematicUnit.h"

DynamicGroupVelocityMatch::DynamicGroupVelocityMatch(KinematicUnit* pMover, float radius)
:DynamicVelocityMatch(pMover, nullptr)
, mpMover(pMover)
, mRadius(radius)
{
}

Steering* DynamicGroupVelocityMatch::getSteering()
{
	Vector2D average_velocity(0, 0);
	int neighbors = 0;
	for (size_t i = 0; i < UNIT_MANAGER->m_units.size(); i++)
	{
		KinematicUnit *temp = UNIT_MANAGER->m_units[i];
		Vector2D direction = mpMover->getPosition() - temp->getPosition();
		float distance = direction.getLength();

		if (distance < mRadius)
		{
			average_velocity += temp->getVelocity();
			neighbors++;
		}
	}
	average_velocity /= neighbors;

	KinematicUnit temp(gpGame->getSpriteManager()->getSprite(2), "NULL", gZeroVector2D, 0.0f, average_velocity, 0.0f);
	mpTarget = &temp;

	return DynamicVelocityMatch::getSteering();
}