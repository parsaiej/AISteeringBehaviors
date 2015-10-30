#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "KinematicUnitManager.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"
#include "DynamicAlignSteering.h"
#include "DynamicPursueSteering.h"
#include "DynamicFaceSteering.h"
#include "DynamicWanderSteering.h"
#include "WanderAndSeekOrFlee.h"
#include "DynamicSeparationSteering.h"
#include "DynamicCohesionSteering.h"
#include "DynamicFlockingSteering.h"
#include "DynamicVelocityMatch.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, std::string id, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration, float maxRotation, float maxRotationalVelocity)
:Kinematic( position, orientation, velocity, rotationVel )
,mpSprite(pSprite)
,mpCurrentSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
, mMaxRotation(maxRotation)
, mMaxRotationalVelocity(maxRotationalVelocity)
{
	mID = id;
}

KinematicUnit::~KinematicUnit()
{
	if (mID != "NULL")
		std::cout << "Destroying: " << this->getID() << std::endl;
	delete mpCurrentSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time)
{
	Steering* steering;
	if (mpCurrentSteering != NULL)
		steering = mpCurrentSteering->getSteering();
	else
		steering = &gNullSteering;

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{	
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}
	else
		setNewOrientation();

	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, mMaxRotationalVelocity );

	//move the unit using current velocities
	Kinematic::update(time);

	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	//setNewOrientation();
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget, true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, pTarget );
	setSteering( pDynamicArriveSteering );
}

void KinematicUnit::dynamicAlign(KinematicUnit* pTarget)
{
	DynamicAlignSteering* pDynamicAlignSteering = new DynamicAlignSteering(this, pTarget);
	setSteering(pDynamicAlignSteering);
}

void KinematicUnit::dynamicPursue(KinematicUnit* pTarget)
{
	DynamicPursueSteering* pDynamicPursueSteering = new DynamicPursueSteering(this, pTarget);
	setSteering(pDynamicPursueSteering);
}

void KinematicUnit::dynamicFace(KinematicUnit* pTarget)
{
	DynamicFaceSteering* pDynamicFaceSteering = new DynamicFaceSteering(this, pTarget);
	setSteering(pDynamicFaceSteering);
}

void KinematicUnit::dynamicWander()
{
	DynamicWanderSteering* pDynamicWanderSteering = new DynamicWanderSteering(this);
	setSteering(pDynamicWanderSteering);
}

void KinematicUnit::dynamicWanderAndSeek(KinematicUnit* pTarget, float radius)
{
	WanderAndSeekOrFlee* pWanderAndSeekOrFlee = new WanderAndSeekOrFlee(this, pTarget, false, radius);
	setSteering(pWanderAndSeekOrFlee);
}

void KinematicUnit::dynamicWanderAndFlee(KinematicUnit* pTarget, float radius)
{
	WanderAndSeekOrFlee* pWanderAndSeekOrFlee = new WanderAndSeekOrFlee(this, pTarget, true, radius);
	setSteering(pWanderAndSeekOrFlee);
}

void KinematicUnit::dynamicSeparation()
{
	DynamicSeparationSteering* pDynamicSeparationSteering = new DynamicSeparationSteering(this);
	setSteering(pDynamicSeparationSteering);
}

void KinematicUnit::dynamicCohesion()
{
	DynamicCohesionSteering* pDynamicCohesionSteering = new DynamicCohesionSteering(this, 150.0f);
	setSteering(pDynamicCohesionSteering);
}

void KinematicUnit::dynamicFlocking()
{
	DynamicFlockingSteering* pDynamicFlockingSteering = new DynamicFlockingSteering(this);
	setSteering(pDynamicFlockingSteering);
}

void KinematicUnit::dynamicVelocityMatch(KinematicUnit* pTarget)
{
	DynamicVelocityMatch* pDynamicVelocityMatch = new DynamicVelocityMatch(this, pTarget);
	setSteering(pDynamicVelocityMatch);
}