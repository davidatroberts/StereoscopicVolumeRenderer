#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>

#include "vector.hpp"

class Quaternion
{
public:
	Quaternion(double w, Vector v);

	double norm();
	Quaternion conjugate();
	Quaternion inverse();
	Vector rotate_vector(Vector v);

	static Quaternion create_rotation(const Vector& vec, double angle);
	static Quaternion euler_to_quaternion(double yaw, double pitch, double roll);

	void operator+= (const Quaternion& q);
	void operator-= (const Quaternion& q);
	Quaternion operator+ (const Quaternion& q);
	Quaternion operator- (const Quaternion& q);
	Quaternion operator* (Quaternion& rhs);
	Quaternion operator/ (const double& rhs);
	bool operator== (const Quaternion& q) const;

	double w;
	Vector v;
};

#endif