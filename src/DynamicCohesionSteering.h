//#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"

class KinematicUnit;

class DynamicCohesionSteering : public DynamicArriveSteering
{
public:
	DynamicCohesionSteering(KinematicUnit* pMover, float mNeighborRadius);
	~DynamicCohesionSteering() {};

	virtual Steering* getSteering();
private:
	KinematicUnit* mpMover;
	float mNeighborRadius;
};