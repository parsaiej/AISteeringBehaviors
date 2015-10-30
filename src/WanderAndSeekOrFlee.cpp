#include "WanderAndSeekOrFlee.h"
#include "KinematicUnit.h"
#include "DynamicWanderSteering.h"
#include "DynamicSeekSteering.h"

#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

WanderAndSeekOrFlee::WanderAndSeekOrFlee(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee, float radius)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mRadius(radius)
	, mShouldFlee(shouldFlee)
{
	mpDynamicWanderSteering = new DynamicWanderSteering(pMover);
	mpDynamicSeekSteering = new DynamicSeekSteering(pMover, pTarget, shouldFlee);
}

WanderAndSeekOrFlee::~WanderAndSeekOrFlee()
{
	delete mpDynamicWanderSteering;
	mpDynamicWanderSteering = nullptr;

	delete mpDynamicSeekSteering;
	mpDynamicSeekSteering = nullptr;
}

Steering* WanderAndSeekOrFlee::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();
	float distance = direction.getLength();

	ALLEGRO_COLOR color;
	if (mShouldFlee)
		color = al_map_rgb(0, 0, 0);
	else
		color = al_map_rgb(0, 191, 255);

	if (debugOn)
		al_draw_circle(mpMover->getPosition().getX(), mpMover->getPosition().getY(), mRadius, color, 2.0f);

	if (distance > mRadius)
		return mpDynamicWanderSteering->getSteering();
	else
		return mpDynamicSeekSteering->getSteering();
}