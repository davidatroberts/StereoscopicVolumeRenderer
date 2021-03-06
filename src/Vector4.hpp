#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>

#include "Util.hpp"

class Vector4 {
public:
	Vector4(double x, double y, double z, double w);
	Vector4(Colour col);
	Vector4();

	inline
	void associate_colour(double scalar) {
		this->x*=scalar;
		this->y*=scalar;
		this->z*=scalar;
	}

	inline
	double dot(Vector4 &vec) {
		return (x*vec.x) + (y*vec.y) + (z*vec.z) + (w*vec.w);
	}

	inline 
	Vector4 operator+ (const Vector4& vec) {
		return Vector4(x+vec.x, y+vec.y, z+vec.z, w+vec.w);
	}

	inline
	void operator+= (const Vector4& vec) {
		x+=vec.x;
		y+=vec.y;
		z+=vec.z;
		w+=vec.w;
	}

	inline
	void operator+= (const Colour& col) {
		x+=col.red;
		y+=col.green;
		z+=col.blue;
		w+=col.alpha;
	}

	inline
	Vector4 operator*(double scalar) {
		return Vector4(this->x*scalar, this->y*scalar, this->z*scalar, this->w*scalar);
	}

	inline friend
	Vector4 operator* (double scalar, Vector4& vec) {
		return Vector4(vec.x*scalar, vec.y*scalar, vec.z*scalar, vec.w*scalar);
	}

	inline 
	Vector4 operator* (const Vector4& vec) {
		return Vector4(x*vec.x, y*vec.y, z*vec.z, w*vec.w);
	}

	double x;
	double y;
	double z;
	double w;
};

#endif