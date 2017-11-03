#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <ostream>
#include <string>

#include "Util.hpp"
#include "Matrix3.hpp"

class Vector
{
public:
	Vector(double x=0, double y=0, double z=0);
	Vector(Colour col);

	Vector mult_scalar(double scalar);
	double p_norm(double p);
	double magnitude();
	Vector normalized();

	inline
	double dot(Vector &vec) {
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}
	
	inline
	double distance(Vector &vec) {
		double xd = x - vec.x;
		double yd = y - vec.y;
		double zd = z - vec.z;
		return sqrt(xd*xd + yd*yd + zd*zd);
	}

	double normalized_distance(Vector &normalized_distance);
	double distance_squared(Vector &vec);
	
	inline
	Vector map_range(Vector &a_vec, Vector &b_vec, Vector &c_vec, Vector &d_vec) {
		return Vector(Util::map_range(a_vec.x, b_vec.x, c_vec.x, d_vec.x, x), 
			Util::map_range(a_vec.y, b_vec.y, c_vec.y, d_vec.y, y), 
			Util::map_range(a_vec.z, b_vec.z, c_vec.z, d_vec.z, z));
	};

	Vector round_vec();
	Vector rotate_x(double angle_degree);
	Vector rotate_y(double angle_degree);
	Vector rotate_z(double angle_degree);
	Vector rotate_xyz(double x_deg, double y_deg, double z_deg);

	Vector operator+ (const Vector& vec);
	Vector operator+ (double scalar);

	inline
	void operator+= (const Vector& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	void operator*= (double scalar);

	Vector operator- (double scalar);

	inline
	Vector operator- (const Vector& vec) {
		return Vector(x-vec.x, y-vec.y, z-vec.z);
	}

	Vector operator/ (double scalar);

	inline
	Vector operator/ (const Vector& vec) {
		return Vector(x/vec.x, y/vec.y, z/vec.z);
	}

	Vector operator* (Matrix3& m) const;
	inline
	Vector operator* (double scalar) const {
		return Vector(x*scalar, y*scalar, z*scalar);
	};

	inline
	Vector operator* (const Vector& vec) const {
		return Vector(x*vec.x, y*vec.y, z*vec.z);
	}

	inline friend Vector operator* (double lhs, const Vector& rhs) {
		return Vector(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z);
	}

	friend std::ostream& operator<<(std::ostream &strm, Vector &v);

	Vector operator^ (const Vector& vec);
	bool operator== (const Vector &vec) const;
	bool operator!= (const Vector &vec);

	double x;
	double y;
	double z;
};

#endif