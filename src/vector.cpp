#include "vector.hpp"

#include <ostream>

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector::Vector(const Colour &col) : x(col.red), y(col.green), z(col.blue) {}

Vector Vector::mult_scalar(double scalar) const {
	return {x * scalar, y * scalar, z * scalar};
}

double Vector::p_norm(double p) const {
	double px = pow(x, p);
	double py = pow(y, p);
	double pz = pow(z, p);

	double sqr = px + py + pz;
	return pow(sqr, 1.0 / p);
}

double Vector::magnitude() const {
	return p_norm(2);
}

Vector Vector::normalized() const {
	return mult_scalar(1 / magnitude());
}

double Vector::distance_squared(const Vector &vec) const {
	double xd = x - vec.x;
	double yd = y - vec.y;
	double zd = z - vec.z;

	return xd * xd + yd * yd + zd * zd;
}

Vector Vector::round_vec() const {
	return {round(x + 0.5), round(y + 0.5), round(z + 0.5)};
}

Vector Vector::rotate_x(double angle_degree) const {
	double radians = angle_degree * (M_PI / 180.0);
	Matrix3 rm = Matrix3::x_matrix(radians);

	return *this * rm;
}

Vector Vector::rotate_y(double angle_degree) const {
	double radians = angle_degree * (M_PI / 180.0);
	return *this * Matrix3::y_matrix(radians);
}

Vector Vector::rotate_z(double angle_degree) const {
	double radians = angle_degree * (M_PI / 180.0);
	return *this * Matrix3::z_matrix(radians);
}

Vector Vector::rotate_xyz(double x_deg, double y_deg, double z_deg) const {
	double x_radians = x_deg * (M_PI / 180.0);
	double y_radians = y_deg * (M_PI / 180.0);
	double z_radians = z_deg * (M_PI / 180.0);

	const auto xm = Matrix3::x_matrix(x_radians);
	const auto ym = Matrix3::y_matrix(y_radians);
	const auto zm = Matrix3::z_matrix(z_radians);

	const auto xym = xm * ym;
	const auto xyzm = xym * zm;

	return *this * xyzm;
}

void Vector::operator*=(double scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

Vector Vector::operator+(const Vector &vec) const {
	return {x + vec.x, y + vec.y, z + vec.z};
}

Vector Vector::operator+(double scalar) const {
	return {x + scalar, y + scalar, z + scalar};
}

Vector Vector::operator-(double scalar) const {
	return {x - scalar, y - scalar, z - scalar};
}

Vector Vector::operator/(double scalar) const {
	return {x / scalar, y / scalar, z / scalar};
}

Vector Vector::operator*(const Matrix3 &m) const {
	Vector vec;
	vec.x = (m.get(0, 0) * x) + (m.get(1, 0) * y) + (m.get(2, 0) * z);
	vec.y = (m.get(0, 1) * x) + (m.get(1, 1) * y) + (m.get(2, 1) * z);
	vec.z = (m.get(0, 2) * x) + (m.get(1, 2) * y) + (m.get(2, 2) * z);

	return vec;
}

Vector Vector::operator^(const Vector &vec) const {
	return {y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x};
}

bool Vector::operator==(const Vector &vec) const {
	// todo(droberts): use float comparison here
	if ((x == vec.x) && (y == vec.y) && (z == vec.z)) {
		return true;
	}
	return false;
}

bool Vector::operator!=(const Vector &vec) const {
	return !(*this == vec);
}

std::ostream &operator<<(std::ostream &os, const Vector &v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}
