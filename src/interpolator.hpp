#pragma once

#include "matrix_3d.hpp"
#include "vector.hpp"

class Interpolator {
public:
	Interpolator(Vector min, Vector max)
		: min_(min), max_(max), width_(max_.x - min_.x), height_(max_.y - min_.y), depth_(max_.z - min_.z) {}

	virtual ~Interpolator() {}

	virtual void preprocess(Matrix3D &mat) = 0;
	virtual double interpolate(const Vector &position, const Matrix3D &mat) const = 0;

protected:
	Vector min_;
	Vector max_;
	int width_;
	int height_;
	int depth_;
};
