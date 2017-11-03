#ifndef TRILINEAR_INTERPOLATOR
#define TRILINEAR_INTERPOLATOR

#include "CCInterpolator.hpp"

class CCTrilinear: public CCInterpolator {
public:
	CCTrilinear(Vector min, Vector max);

	~CCTrilinear();

	void preprocess(Matrix3D &mat);
	double interpolate(Vector &position, Matrix3D &mat);
};

#endif