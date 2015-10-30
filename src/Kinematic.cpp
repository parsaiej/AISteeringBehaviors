#include "Kinematic.h"
#include "Steering.h"

Vector2D gZeroVector(0,0);

Kinematic::Kinematic(const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel)
:mPosition( position )
,mOrientation( orientation )
,mVelocity( velocity )
,mRotationVel( rotationVel )
{
}

Kinematic::~Kinematic()
{
}

void Kinematic::update( float time)
{
	mPosition += mVelocity * time;
	mOrientation += mRotationVel * time;
}

void Kinematic::calcNewVelocities( const Steering& theSteering, float time, float maxSpeed, float maxRotationalVelocity )
{
	mVelocity += theSteering.getLinear() * time;
	mRotationVel += theSteering.getAngular() * time;

	//cap the velocities
	capVelocity( maxSpeed );
	if( mRotationVel > maxRotationalVelocity )
	{
		mRotationVel = maxRotationalVelocity;
	}
}

al_fixed Kinematic::getRotation() const
{
	return getRotationFromRadians( mOrientation );
}

void Kinematic::capVelocity( float maxSpeed )
{
	if( mVelocity.getLengthSquared() > ( maxSpeed * maxSpeed ) )
	{
		mVelocity.normalize();
		mVelocity *= maxSpeed;
	}
}

Vector2D Kinematic::getOrientationAsVector()
{
	//std::cout << mOrientation << " : " << sinf(mOrientation) << ", " << cosf(mOrientation) << std::endl;

	return Vector2D( sinf(mOrientation), cosf(mOrientation) );
}

//static
al_fixed Kinematic::getRotationFromRadians( float radians )
{
	al_fixed angle = al_ftofix (radians * 128 / PI);
	return angle;
}

//static
float Kinematic::getOrientationFromVelocity( float currentOrientation, const Vector2D& velocity )
{
	if( velocity.hasNonZeroLength() )
	{
		currentOrientation = atan2(velocity.getX(), -velocity.getY()); 
	}
	return currentOrientation;
}
