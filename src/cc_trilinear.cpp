#include "cc_trilinear.hpp"

CCTrilinear::CCTrilinear(Vector min, Vector max) : CCInterpolator(min, max) {}

CCTrilinear::~CCTrilinear() {}

void CCTrilinear::preprocess(Matrix3D &mat) {}

double CCTrilinear::interpolate(const Vector &position, const Matrix3D &mat) const {
	int i = static_cast<unsigned int>(position.x);
	int j = static_cast<unsigned int>(position.y);
	int k = static_cast<unsigned int>(position.z);

	float bx = position.x - static_cast<float>(i);
	float by = position.y - static_cast<float>(j);
	float bz = position.z - static_cast<float>(k);

	return (
		mat(i, j, k) * (1.0f - bx) * (1.0f - by) * (1.0f - bz) + mat(i + 1, j, k) * bx * (1.0f - by) * (1.0f - bz) +
		mat(i + 1, j + 1, k) * bx * by * (1.0f - bz) + mat(i, j + 1, k) * (1.0f - bx) * by * (1.0f - bz) +
		mat(i, j, k + 1) * (1.0f - bx) * (1.0f - by) * bz + mat(i + 1, j, k + 1) * bx * (1.0f - by) * bz +
		mat(i + 1, j + 1, k + 1) * bx * by * bz + mat(i, j + 1, k + 1) * (1.0f - bx) * by * bz);
}
