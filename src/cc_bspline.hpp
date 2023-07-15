#ifndef BSPLINE_INTERPOLATOR
#define BSPLINE_INTERPOLATOR

#include "cc_interpolator.hpp"
#include "vector4.hpp"

class CCBSpline : public CCInterpolator {
public:
	CCBSpline(Vector min, Vector max);

	~CCBSpline();

	void preprocess(Matrix3D &mat) override;
	double interpolate(const Vector &position, const Matrix3D &mat) const override;

private:
	Vector4 weight_coefficients_[4];
};

#endif
