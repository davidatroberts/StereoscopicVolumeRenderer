#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>

#include "util.hpp"

class Vector4 {
public:
	Vector4() = default;
	Vector4(double x, double y, double z, double w);
	explicit Vector4(const Colour& col);

	inline void associate_colour(double scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	inline double dot(const Vector4& vec) const {
		return (x * vec.x) + (y * vec.y) + (z * vec.z) + (w * vec.w);
	}

	inline Vector4 operator+(const Vector4& vec) {
		return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	inline void operator+=(const Vector4& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
	}

	inline void operator+=(const Colour& col) {
		x += col.red;
		y += col.green;
		z += col.blue;
		w += col.alpha;
	}

	inline Vector4 operator*(double scalar) {
		return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
	}

	inline friend Vector4 operator*(double scalar, Vector4& vec) {
		return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	inline Vector4 operator*(const Vector4& vec) {
		return Vector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}

	double x{0.0};
	double y{0.0};
	double z{0.0};
	double w{0.0};
};

#endif
