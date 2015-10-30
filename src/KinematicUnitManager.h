#pragma once

#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "KinematicUnit.h"
#include "Game.h"
#include "GraphicsSystem.h"

//WILL SOON BE MOVING THIS LOGIC TO KINEMATICUNITMANAGER.H
/*############################################################################*/
enum SteeringType
{
	INVALID_STEERTYPE = -1,
	SEEK,
	ARRIVE,
	FLEE,
	WANDER,
	ALIGN,
	PURSUE,
	FACE,
	WANDERSEEK,
	WANDERFLEE,
	SEPARATE,
	COHESION,
	FLOCKING,
	VELOCITYMATCH,
	NUM_STEERTYPES
};

const std::string mTypeArray[] = { "Seek", "Arrive", "Flee", "Wander", "Align", "Pursue", "Face", "WanderAndSeek", "WanderAndFlee", "Separate", "Cohesion", "Flocking", "VelocityMatch" };
/*############################################################################*/

class KinematicUnitManager : public Trackable
{
public:
	KinematicUnitManager();
	~KinematicUnitManager();

	KinematicUnit* getKinematicUnit(std::string);
	int getNumKinematicUnits();

	void addKinematicUnit(KinematicUnit*);

	void removeKinematicUnit(std::string);
	void removeKinematicUnit(KinematicUnit *kunit);
	void removeRandomKinematicUnit();
	void removeAllBoids();

	void update(float dTime);
	void displayUnitCount();

	void draw();
	void clear();

	friend class DynamicSeparationSteering;
	friend class DynamicGroupAlignSteering;
	friend class DynamicCohesionSteering;
	friend class DynamicGroupVelocityMatch;
private:
	std::vector<KinematicUnit*> m_units;
};