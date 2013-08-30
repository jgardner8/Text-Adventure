#pragma once

#include <math.h>
#include <cstdlib>

//Includes min, excludes max [min, max). Min/max are positive integers.
inline int Random(int min, int max) { 
	return (rand() % (max - min)) + min; 
}

//Includes min, excludes max [min, max). Min/max are positive numbers
inline float Random(float min, float max) { 
	return (rand() / (float)RAND_MAX) * (max - min) + min; 
}

//Randomly makes a float positive or negative. (eg. input -13, get either 13 or -13 back)
inline float PosOrNeg(float num) {
	return num * (Random(0, 2) == 0 ? 1 : -1);
}

inline float round(float num) {
	return (num > 0.f) ? floor(num + 0.5f) : ceil(num - 0.5f);
}

inline double round(double num) {
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}

inline int roundi(float num) {
	return (num > 0.f) ? (int)floor(num + 0.5f) : (int)ceil(num - 0.5f);
}

inline int roundi(double num) {
	return (num > 0.0) ? (int)floor(num + 0.5) : (int)ceil(num - 0.5);
}