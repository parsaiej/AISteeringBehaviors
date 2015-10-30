#include "KinematicArriveSteering.h"
#include "KinematicUnit.h"

#include <string>
#include <strstream>

KinematicArriveSteering::KinematicArriveSteering(KinematicUnit *pMover, const Vector2D &targetPosition, float satisfactionRadius, float timeToTarget)
:mpMover(pMover)
,mTarget(targetPosition)
,mSatisfactionRadius(satisfactionRadius)
,mTimeToTarget(timeToTarget)
{
	mApplyDirectly = true;
}

Steering* KinematicArriveSteering::getSteering()
{
	mLinear = mTarget - mpMover->getPosition();

	//debug code!!!!
	/*std::strstream theStream;
	theStream << "Steering: Linear velocity: " << mLinear.getX() << ":" << mLinear.getY() << " length = " << mLinear.getLength() << "\n";
	gpSystem->writeToConsole( theStream.str() );

	std::strstream theStream2;
	theStream2 << "Mover: velocity: " << mpMover->getVelocity().getX() << ":" << mpMover->getVelocity().getY() << " length = " << mpMover->getVelocity().getLength() << "\n";
	gpSystem->writeToConsole( theStream2.str() );
	//message*/

	//inside the satisfaction radius?
	if( mLinear.getLengthSquared() < mSatisfactionRadius * mSatisfactionRadius )
	{
		mLinear = gZeroVector2D;
		mAngular = mpMover->getOrientation();
		return this;
	}

	//calc how long we'd like it to take to get there
	mLinear /= mTimeToTarget;

	float maxVelocity = mpMover->getMaxVelocity();//for efficiency

	if( mLinear.getLengthSquared() > maxVelocity * maxVelocity )//velocity too great?
	{
		//cap the velocity
		mLinear.normalize();
		mLinear *= maxVelocity;
	}

	mAngular = Kinematic::getOrientationFromVelocity( mpMover->getOrientation(), mLinear );

	return this;
}