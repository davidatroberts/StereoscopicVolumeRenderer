#ifndef TRILINEAR_INTERPOLATOR
#define TRILINEAR_INTERPOLATOR

#include "cc_interpolator.hpp"

class CCTrilinear : public CCInterpolator {
public:
	CCTrilinear(Vector min, Vector max);

	~CCTrilinear();

	void preprocess(Matrix3D &mat);
	double interpolate(const Vector &position, const Matrix3D &mat) const;
};

#endif
