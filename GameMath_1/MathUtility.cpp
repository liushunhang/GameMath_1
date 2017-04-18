#include "MathUtility.h"
#include "Vector3.h"

const Vector3 KZeroVector(0.0f, 0.0f, 0.0f);
float wrapPi(float theta)
{
	theta += kPi;
	theta -= floor(theta*k1Over2Pi)*k2Pi;
	theta -= kPi;
	return theta;
}

float SafeAcos(float theta)
{
	if (theta < -1.0f)
	{
		return kPi;
	}
	if (theta > 1.0f)
	{
		return 0.0f;
	}
	return acos(theta);
}
