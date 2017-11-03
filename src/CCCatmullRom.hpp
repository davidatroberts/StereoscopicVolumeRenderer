#ifndef CATMULL_ROM_INTERPOLATOR_H
#define CATMULL_ROM_INTERPOLATOR_H

#include "CCInterpolator.hpp"
#include "Vector4.hpp"
#include "Matrix3D.hpp"

class CCCatmullRom: public CCInterpolator
{
public:
	CCCatmullRom(Vector min, Vector max);

	~CCCatmullRom();

	void preprocess(Matrix3D &mat);
	double interpolate(Vector &position, Matrix3D &mat);

private:
	Vector4 weight_coefficients_[4];
};

#endif