#pragma once

#include "interpolator.hpp"

class CCInterpolator : public Interpolator {
public:
	CCInterpolator(Vector min, Vector max) : Interpolator(min, max) {}
};
