#include "Vector.hpp"

Vector::Vector(double x, double y, double z): x(x), y(y), z(z) {
}

Vector::Vector(Colour col) {
	x = col.red;
	y = col.green;
	z = col.blue;
}

Vector Vector::mult_scalar(double scalar) {
	Vector vec(this->x, this->y, this->z);
	vec.x = vec.x * scalar;
	vec.y = vec.y * scalar;
	vec.z = vec.z * scalar;

	return vec;
}

double Vector::p_norm(double p) {
	double x = pow(this->x, p);
	double y = pow(this->y, p);
	double z = pow(this->z, p);

	double sqr = x+y+z;
	return pow(sqr, 1.0/p);
}

double Vector::magnitude() {
	return this->p_norm(2);
}

Vector Vector::normalized() {
	double magnitude = this->magnitude();
	return this->mult_scalar(1/magnitude);
}

double Vector::normalized_distance(Vector &normalized_result) {
	Vector copy(x, y, z);
	double old_length = distance(copy);

	if (old_length < Util::epsilon) {
		old_length = 1;
	}

	normalized_result = copy/old_length;
	return old_length;
}

double Vector::distance_squared(Vector &vec) {
	double xd = this->x - vec.x;
	double yd = this->y - vec.y;
	double zd = this->z - vec.z;

	return xd*xd + yd*yd + zd*zd;
}

Vector Vector::round_vec() {
	return Vector(round(this->x+0.5), round(this->y+0.5), round(this->z+0.5));
} 

Vector Vector::rotate_x(double angle_degree) {
	double radians = angle_degree * (M_PI/180.0);
	Matrix3 rm = Matrix3::x_matrix(radians);

	Vector vec = *this * rm;
	return vec;
}

Vector Vector::rotate_y(double angle_degree) {
	double radians = angle_degree * (M_PI/180.0);
	Matrix3 rm = Matrix3::y_matrix(radians);

	Vector vec = *this * rm;
	return vec;
}

Vector Vector::rotate_z(double angle_degree) {
	double radians = angle_degree * (M_PI/180.0);
	Matrix3 rm = Matrix3::z_matrix(radians);

	Vector vec = *this * rm;
	return vec;
}

Vector Vector::rotate_xyz(double x_deg, double y_deg, double z_deg) {
	double x_radians = x_deg * (M_PI/180.0);
	double y_radians = y_deg * (M_PI/180.0);
	double z_radians = z_deg * (M_PI/180.0);

	Matrix3 xm = Matrix3::x_matrix(x_radians);
	Matrix3 ym = Matrix3::y_matrix(y_radians);
	Matrix3 zm = Matrix3::z_matrix(z_radians);

	Matrix3 xym = xm * ym;
	Matrix3 xyzm = xym * zm;

	Vector vec = *this * xyzm;
	return vec;
}

void Vector::operator*= (double scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

Vector Vector::operator+ (const Vector& vec) {
	return Vector(x + vec.x, y + vec.y, z + vec.z);
}

Vector Vector::operator+ (double scalar) {
	return Vector(x + scalar, y + scalar, z + scalar);
}

Vector Vector::operator- (double scalar) {
	return Vector(x - scalar, y - scalar, z - scalar);;
}

Vector Vector::operator/ (double scalar) {
	return Vector(x/scalar, y/scalar, z/scalar);
}

Vector Vector::operator* (Matrix3& m) const {
	Vector vec;
	vec.x = (m.get(0, 0) * x) + (m.get(1, 0) * y) + (m.get(2, 0) * z);
	vec.y = (m.get(0, 1) * x) + (m.get(1, 1) * y) + (m.get(2, 1) * z);
	vec.z = (m.get(0, 2) * x) + (m.get(1, 2) * y) + (m.get(2, 2) * z);

	return vec;
}

Vector Vector::operator^ (const Vector& vec) {
	Vector result(y * vec.z - z * vec.y, 
				  z * vec.x - x * vec.z, 
				  x * vec.y - y * vec.x);
	return result;
}

bool Vector::operator== (const Vector &vec) const{
	if ((x==vec.x) && (y==vec.y) && (z==vec.z)) {
		return true;
	}
	return false;
}

bool Vector::operator!= (const Vector &vec) {
	if ((x==vec.x) && (y==vec.y) && (z==vec.z)) {
		return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream &strm, Vector &v) {
	strm << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return strm;
}