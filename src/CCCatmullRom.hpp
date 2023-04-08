#ifndef CATMULL_ROM_INTERPOLATOR_H
#define CATMULL_ROM_INTERPOLATOR_H

#include "CCInterpolator.hpp"
#include "Matrix3D.hpp"
#include "Vector4.hpp"

class CCCatmullRom : public CCInterpolator {
public:
	CCCatmullRom(Vector min, Vector max);

	~CCCatmullRom();

	void preprocess(Matrix3D &mat);
	double interpolate(const Vector &position, const Matrix3D &mat) const;

private:
	Vector4 weight_coefficients_[4];
};

#endif
