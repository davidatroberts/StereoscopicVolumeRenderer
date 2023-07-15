#ifndef CC_INTERPOLATOR
#define CC_INTERPOLATOR

#include "interpolator.hpp"

class CCInterpolator : public Interpolator {
public:
	CCInterpolator(Vector min, Vector max) : Interpolator(min, max) {}
};

#endif
