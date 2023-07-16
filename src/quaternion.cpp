#include "quaternion.hpp"

Quaternion::Quaternion(double w, Vector v) : w(w), v(v) {}

double Quaternion::norm() {
	return (w * w) + (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

Quaternion Quaternion::conjugate() {
	return Quaternion(w, Vector(-v.x, -v.y, -v.z));
}

Quaternion Quaternion::inverse() {
	return conjugate() / norm();
}

Quaternion Quaternion::create_rotation(const Vector& vec, double angle) {
	double a = (angle * (M_PI / 180.0)) / 2.0;
	Vector v = vec * sin(a);
	double w = cos(a);

	return Quaternion(w, v);
}

Quaternion Quaternion::euler_to_quaternion(double yaw, double pitch, double roll) {
	double yaw_r = yaw * (M_PI / 180.0);
	double pitch_r = pitch * (M_PI / 180.0);
	double roll_r = roll * (M_PI / 180.0);

	double c1 = cos(yaw_r / 2);
	double s1 = sin(yaw_r / 2);
	double c2 = cos(pitch_r / 2);
	double s2 = sin(pitch_r / 2);
	double c3 = cos(roll_r / 2);
	double s3 = sin(roll_r / 2);

	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;

	return Quaternion(
		c1c2 * c3 - s1s2 * s3, Vector(c1c2 * s3 + s1s2 * c3, s1 * c2 * c3 + c1 * s2 * s3, c1 * s2 * c3 - s1 * c2 * s3));
}

Vector Quaternion::rotate_vector(Vector v) {
	Quaternion vq(0, v);
	Quaternion inv = inverse();
	Quaternion result = ((*this) * vq) * inv;

	return result.v;
}

void Quaternion::operator+=(const Quaternion& q) {
	w += q.w;
	v += q.v;
}

void Quaternion::operator-=(const Quaternion& q) {
	w -= q.w;
	v = v - q.v;  // get around weird compilation error
}

Quaternion Quaternion::operator+(const Quaternion& q) {
	return Quaternion(w + q.w, v + q.v);
}

Quaternion Quaternion::operator-(const Quaternion& q) {
	return Quaternion(w - q.w, v - q.v);
}

Quaternion Quaternion::operator*(Quaternion& rhs) {
	Vector res_v(
		w * rhs.v.x + v.x * rhs.w + v.y * rhs.v.z - v.z * rhs.v.y,
		w * rhs.v.y + v.y * rhs.w + v.z * rhs.v.x - v.x * rhs.v.z,
		w * rhs.v.z + v.z * rhs.w + v.x * rhs.v.y - v.y * rhs.v.x);

	return Quaternion(w * rhs.w - v.x * rhs.v.x - v.y * rhs.v.y - v.z * rhs.v.z, res_v);
}

Quaternion Quaternion::operator/(const double& rhs) {
	return Quaternion(w / rhs, v / rhs);
}

bool Quaternion::operator==(const Quaternion& q) const {
	return w == q.w && v == q.v;
}
