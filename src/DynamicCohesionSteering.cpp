#include "DynamicCohesionSteering.h"
#include "SpriteManager.h"
#include "KinematicUnit.h"

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

DynamicCohesionSteering::DynamicCohesionSteering(KinematicUnit* pMover, float neighborRadius)
:DynamicArriveSteering(pMover, nullptr)
	, mpMover(pMover)
	, mNeighborRadius(neighborRadius)
{
	mApplyDirectly = false;
}

Steering* DynamicCohesionSteering::getSteering()
{
	if (debugOn)
		al_draw_circle(mpMover->getPosition().getX(), mpMover->getPosition().getY(), mNeighborRadius, al_map_rgb(0, 191, 255), 2.0f);

	Vector2D centerOfMass = Vector2D(0, 0);
	int neighbors = 0;
	for (size_t i = 0; i < UNIT_MANAGER->m_units.size(); i++)
	{
		KinematicUnit *temp = UNIT_MANAGER->m_units[i];
		if (temp != mpMover)
		{
			Vector2D direction = mpMover->getPosition() - temp->getPosition();
			float distance = direction.getLength();

			if (distance < mNeighborRadius)
			{
				centerOfMass = Vector2D(centerOfMass.getX() + temp->getPosition().getX(), centerOfMass.getY() + temp->getPosition().getY());
				neighbors++;
			}
		}
	}
	
	if (neighbors == 0)
		return this;

	centerOfMass = Vector2D(centerOfMass.getX() / neighbors, centerOfMass.getY() / neighbors);

	KinematicUnit temp(gpGame->getSpriteManager()->getSprite(2), "NULL", centerOfMass, 0.0f, gZeroVector2D, 0.0f);
	mpTarget = &temp;

	return DynamicArriveSteering::getSteering();
}