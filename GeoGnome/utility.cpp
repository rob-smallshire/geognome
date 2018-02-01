#define _USE_MATH_DEFINES
#include <cmath>

#include "utility.hpp"

float deg2rad(float degrees)
{
	float radians = (degrees / 180.0f) * static_cast<float>(M_PI);
	return radians;
}