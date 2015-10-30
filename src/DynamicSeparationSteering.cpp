#include "DynamicSeparationSteering.h"
#include "KinematicUnit.h"
#include "KinematicUnitManager.h"

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

DynamicSeparationSteering::DynamicSeparationSteering(KinematicUnit *pMover, float threshold, float decayCoefficient)
:mpMover(pMover)
, mThreshold(threshold)
, mDecayCoefficient(decayCoefficient)
{
	mApplyDirectly = false;
}

Steering* DynamicSeparationSteering::getSteering()
{
	if (debugOn)
		al_draw_circle(mpMover->getPosition().getX(), mpMover->getPosition().getY(), mThreshold, al_map_rgb(0, 0, 0), 2.0f);

	for (size_t i = 0; i < UNIT_MANAGER->m_units.size(); i++)
	{
		KinematicUnit *temp = UNIT_MANAGER->m_units[i];

		if (temp != mpMover)
		{
			//The book says to take the mover position from the target, but I feel like "separation is more visual when doing vice versa
			Vector2D direction = temp->getPosition() - mpMover->getPosition();//mpMover->getPosition() - temp->getPosition();
			float distance = direction.getLength();

			if (distance < mThreshold)
			{
				if (debugOn)
					al_draw_line(mpMover->getPosition().getX(), mpMover->getPosition().getY(), temp->getPosition().getX(), temp->getPosition().getY(), al_map_rgb(255, 0, 0), 2.0f);

				float strength = min(mDecayCoefficient * distance * distance, mpMover->getMaxAcceleration());
				direction.normalize();
				mLinear = direction * strength;
			}
		}
	}
	mLinear *= -1;
	//mAngular = 0;
	return this;
}