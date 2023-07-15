#ifndef PREFILTERED_BSPLINE_H
#define PREFILTERED_BSPLINE_H

#include "cc_interpolator.hpp"
#include "vector4.hpp"

class CCPrefilteredBSpline : public CCInterpolator {
public:
	CCPrefilteredBSpline(Vector min, Vector max);
	CCPrefilteredBSpline(const CCPrefilteredBSpline &other);

	~CCPrefilteredBSpline();

	void preprocess(Matrix3D &mat);
	double interpolate(const Vector &position, const Matrix3D &mat) const;

	friend void swap(CCPrefilteredBSpline &first, CCPrefilteredBSpline &second);
	CCPrefilteredBSpline &operator=(CCPrefilteredBSpline spline);

private:
	void samples_to_coefficients(float *volume);
	void samples_to_coefficientsX(
		float *volume, unsigned int pitch, unsigned int width, unsigned int height, unsigned int depth);
	void samples_to_coefficientsY(
		float *volume, unsigned int pitch, unsigned int width, unsigned int height, unsigned int depth);
	void samples_to_coefficientsZ(
		float *volume, unsigned int pitch, unsigned int width, unsigned int height, unsigned int depth);
	void convert_to_coefficients(float *coeffs, int data_length, int step);
	float initial_causal_coefficient(float *coeffs, int data_length, int step);
	float initial_anticausal_coefficient(float *coeffs, int data_length, int step);

	float *coeffs_;
	Vector4 weight_coefficients_[4];
};

#endif
