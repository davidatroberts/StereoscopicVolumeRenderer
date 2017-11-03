#ifndef BSPLINE_INTERPOLATOR
#define BSPLINE_INTERPOLATOR

#include "CCInterpolator.hpp"

#include "Vector4.hpp"

class CCBSpline: public CCInterpolator {
public:
	CCBSpline(Vector min, Vector max);

	~CCBSpline();

	void preprocess(Matrix3D &mat);
	double interpolate(Vector &position, Matrix3D &mat);

private:
	Vector4 weight_coefficients_[4];
};

#endif