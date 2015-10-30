#include "Steering.h"
#include <fstream>

class KinematicUnit;

enum WeightModifier
{
	INVALID_WEIGHT_TYPE = -1,
	WEIGHT_SEPARATION,
	WEIGHT_COHESION,
	WEIGHT_GROUP_ALIGNMENT,
	WEIGHT_GROUP_VELOCITY_MATCH
};

struct BehaviorAndWeight
{
	Steering *behavior;
	float weight;
};

class DynamicFlockingSteering : public Steering
{
public:
	DynamicFlockingSteering(KinematicUnit* pMover);
	~DynamicFlockingSteering();

	virtual Steering* getSteering();

	static void modifyWeight(const WeightModifier &, float);

	static void loadWeights();
	static void dumpWeights();
private:
	static void drawWeights();
	void refreshWeights();

	KinematicUnit* mpMover;
	std::vector<BehaviorAndWeight> mBehaviorVector;

	/*
	static float mWeightSeparation,
		mWeightCohesion,
		mWeightGroupAlignment,
		mWeightGroupVelocityMatch;*/
};

extern float mWeightSeparation,
mWeightCohesion,
mWeightGroupAlignment,
mWeightGroupVelocityMatch;