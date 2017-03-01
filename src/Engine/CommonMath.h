#pragma once

#include <cmath>

#include "Constants.h"

inline CFloat PI() {
	return static_cast<CFloat>(atan(1) * 4);
}

inline CFloat Radians(CFloat degrees) {
	return (degrees * 2 * PI()) / 180;
}

inline CFloat Degrees(CFloat radians) {
	return (radians * 180) / (2 * PI());
}

inline CFloat Sin(CFloat degrees) {
#ifndef CPU_64
	return Degrees(sinf(Radians(degrees)));
#else
	return Degrees(sin(Radians(degrees)));
#endif
}

inline CFloat Cos(CFloat degrees) {
#ifndef CPU_64
	return Degrees(cosf(Radians(degrees)));
#else
	return Degrees(cos(Radians(degrees)));
#endif
}

inline CFloat FMod(CFloat x, CFloat y) {
#ifndef CPU_64
	return fmodf(x, y);
#else
	return fmod(x, y);
#endif
}

inline CFloat ClampAngle(CFloat angle) {
#ifndef CPU_64
	return FMod(angle + 180.0f, 360.0f) - 180.0f;
#else
	return FMod(angle + 180.0, 360.0) - 180.0;
#endif
}