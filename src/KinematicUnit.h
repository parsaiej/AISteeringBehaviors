#pragma once

#include "Kinematic.h"
#include "Steering.h"

/*KinematicUnit - a unit that is derived from the Kinematic class.  Adds behaviors and max speeds and a current Steering.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class Sprite;
class GraphicsBuffer;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

//minmimum forward speed a unit has to have inorder to rotate 
//(keeps unit from spinning in place after stopping
const float MIN_VELOCITY_TO_TURN_SQUARED = 1.0f;

class KinematicUnit: public Kinematic
{
public:
	KinematicUnit(Sprite* pSprite, std::string id, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f, float maxRotation = 1.0f, float maxRotationalVelocity = 5.0f);
	~KinematicUnit();

	//getters and setters
	void setTarget( const Vector2D& target ) { mTarget = target; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	void setVelocity( const Vector2D& velocity ){ mVelocity = velocity; };
	void setPosition(const Vector2D& pos){ mPosition = pos; };
	float getMaxRotation() const { return mMaxRotation; };
	float getMaxRotationalVelocity() const { return mMaxRotationalVelocity; };

	inline std::string getID() const { return mID; }
	inline void setID(std::string id) { mID = id; };

	virtual void setNewOrientation();//face the direction you are moving

	//draw yourself to the indicated buffer
	void draw( GraphicsBuffer* pBuffer );
	//move according to the current velocities and update velocities based on current Steering
	void update(float time);

	//initiate behaviors
	void seek( const Vector2D& target );
	void arrive( const Vector2D& target );
	void wander();
	void dynamicSeek( KinematicUnit* pTarget );
	void dynamicFlee( KinematicUnit* pTarget );
	void dynamicArrive( KinematicUnit* pTarget );
	void dynamicAlign(KinematicUnit* pTarget);
	void dynamicPursue(KinematicUnit* pTarget);
	void dynamicFace(KinematicUnit* pTarget);
	void dynamicWander();
	void dynamicWanderAndSeek(KinematicUnit* pTarget, float radius);
	void dynamicWanderAndFlee(KinematicUnit* pTarget, float radius);
	void dynamicSeparation();
	void dynamicCohesion();
	void dynamicFlocking();
	void dynamicVelocityMatch(KinematicUnit* pTarget);

	void setSteering(Steering* pSteering);
private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	Vector2D mTarget;//used only for Kinematic seek and arrive
	float mMaxVelocity;
	float mMaxAcceleration;
	float mMaxRotation;
	float mMaxRotationalVelocity;

	
	std::string mID;
};