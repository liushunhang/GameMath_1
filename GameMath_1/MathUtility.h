#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H
#include <math.h>
const float kPi = 3.14159265f; //Pi
const float k2Pi = kPi*2.0f;	//2Pi
const float kPiOver2 = kPi / 2.0f; //pi/2
const float k1Over2Pi = 1 / k2Pi; // 1/2pi
const float k1OverPi = 1 / kPi; //1/pi
inline void sinCos(float * returnSin, float * returnCos, float Theta)
{
	*returnSin = sin(Theta);
	*returnCos = cos(Theta);
}
extern float wrapPi(float theta);
extern float SafeAcos(float theta);
#endif // !MATH_UTILITY_H
