#include "DynamicFlockingSteering.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"

#include "DynamicSeparationSteering.h"
#include "DynamicCohesionSteering.h"
#include "DynamicGroupAlignSteering.h"
#include "DynamicGroupVelocityMatch.h"

/*
float DynamicFlockingSteering::mWeightSeparation = 0.1f;
float DynamicFlockingSteering::mWeightCohesion = 0.1f;
float DynamicFlockingSteering::mWeightGroupAlignment = 0.1f;
float DynamicFlockingSteering::mWeightGroupVelocityMatch = 0.1f;*/

float mWeightSeparation = 0.1f;
float mWeightCohesion = 0.1f;
float mWeightGroupAlignment = 0.1f;
float mWeightGroupVelocityMatch = 0.1f;

DynamicFlockingSteering::DynamicFlockingSteering(KinematicUnit* pMover)
	:mpMover(pMover)
{
	loadWeights();
	mApplyDirectly = false;

	BehaviorAndWeight separationBehavior;
	separationBehavior.behavior = new DynamicSeparationSteering(mpMover, 40.0f, 700.0f);
	separationBehavior.weight = mWeightSeparation;

	BehaviorAndWeight cohesionBehavior;
	cohesionBehavior.behavior = new DynamicCohesionSteering(mpMover, 275.0f);
	cohesionBehavior.weight = mWeightCohesion;

	BehaviorAndWeight groupAlignBehavior;
	groupAlignBehavior.behavior = new DynamicGroupAlignSteering(mpMover, 175.0f);
	groupAlignBehavior.weight = mWeightGroupAlignment;

	BehaviorAndWeight groupVelocityBehavior;
	groupVelocityBehavior.behavior = new DynamicGroupVelocityMatch(mpMover, 175.0f);
	groupVelocityBehavior.weight = mWeightGroupVelocityMatch;

	mBehaviorVector.push_back(separationBehavior);
	mBehaviorVector.push_back(cohesionBehavior);
	mBehaviorVector.push_back(groupAlignBehavior);
	mBehaviorVector.push_back(groupVelocityBehavior);
}

DynamicFlockingSteering::~DynamicFlockingSteering()
{
	for (size_t i = 0; i < mBehaviorVector.size(); i++)
		delete mBehaviorVector[i].behavior;
	
	mBehaviorVector.clear();

	dumpWeights();
}

Steering* DynamicFlockingSteering::getSteering()
{
	mLinear = gZeroVector2D;
	mAngular = 0.0f;
	for (size_t i = 0; i < mBehaviorVector.size(); i++)
	{
		Steering* behavior = mBehaviorVector[i].behavior;
		float weight = mBehaviorVector[i].weight;

		Vector2D lin = behavior->getSteering()->getLinear();
		float ang = behavior->getSteering()->getAngular();

		mLinear += lin * weight;
		mAngular += ang * weight;
	}

	mAngular = max(mAngular, mpMover->getMaxRotationalVelocity());
	
	refreshWeights();
	drawWeights();
	return this;
}

//############################### FILE I/O #################################################
void DynamicFlockingSteering::loadWeights()
{
	std::ifstream input("WeightData.txt");
	std::string tempLine;
	while (std::getline(input, tempLine))
	{
		std::string label;
		std::istringstream sStream(tempLine);
		sStream >> label;

		if (label == "SeparationWeight:")
			sStream >> mWeightSeparation;
		else if (label == "CohesionWeight:")
			sStream >> mWeightCohesion;
		else if (label == "GroupAlignWeight:")
			sStream >> mWeightGroupAlignment;
		else if (label == "GroupVelocityWeight:")
			sStream >> mWeightGroupVelocityMatch;
	}
	input.close();
}

void DynamicFlockingSteering::dumpWeights()
{
	std::ofstream output("WeightData.txt", std::ofstream::out | std::ofstream::trunc);
	output << "SeparationWeight: " << mWeightSeparation;
	output << "\nCohesionWeight: " << mWeightCohesion;
	output << "\nGroupAlignWeight: " << mWeightGroupAlignment;
	output << "\nGroupVelocityWeight: " << mWeightGroupVelocityMatch;
	output.close();
}
//#########################################################################################

void DynamicFlockingSteering::modifyWeight(const WeightModifier &modifier, float weightMod)
{
	switch (modifier)
	{
	case 0:
		mWeightSeparation += weightMod;
		break;
	case 1:
		mWeightCohesion += weightMod;
		break;
	case 2:
		mWeightGroupAlignment += weightMod;
		break;
	case 3:
		mWeightGroupVelocityMatch += weightMod;
		break;
	}
}

void DynamicFlockingSteering::drawWeights()
{
	std::stringstream displayStream;
	displayStream << "[BLENDING WEIGHTS]: "
		<< " - SEPARATION[Y/H] = [" <<  mWeightSeparation << "] "
		<< " - COHESION [U/J] = [" << mWeightCohesion << "] "
		<< " - ALIGNMENT MATCH [I/K] = [" << mWeightGroupAlignment << "] "
		<< " - VELOCITY MATCH [O/L] = [" << mWeightGroupVelocityMatch << "]";

	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), GRAPHICS_SYSTEM->getWidth() / 2, GRAPHICS_SYSTEM->getHeight() - 25, ALLEGRO_ALIGN_CENTER, displayStream.str().c_str());
}

void DynamicFlockingSteering::refreshWeights()
{
	//I'll fix the way I'm doing this later... works for now....
	mBehaviorVector[0].weight = mWeightSeparation;
	mBehaviorVector[1].weight = mWeightCohesion;
	mBehaviorVector[2].weight = mWeightGroupAlignment;
	mBehaviorVector[3].weight = mWeightGroupVelocityMatch;
}