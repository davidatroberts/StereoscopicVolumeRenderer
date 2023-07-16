#pragma once

#include "cc_interpolator.hpp"
#include "matrix_3d.hpp"
#include "vector4.hpp"

class CCCatmullRom : public CCInterpolator {
public:
	CCCatmullRom(Vector min, Vector max);

	~CCCatmullRom();

	void preprocess(Matrix3D &mat);
	double interpolate(const Vector &position, const Matrix3D &mat) const;

private:
	Vector4 weight_coefficients_[4];
};
