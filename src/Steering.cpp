#include "Steering.h"

float Steering::mapToRange(float orientation)
{
	
	while ((orientation > PI) || (orientation < -PI))
	{
		if (orientation > PI)
			orientation -= 2 * PI;
		else if (orientation < -PI)
			orientation += 2 * PI;
	}

	return orientation;
}
