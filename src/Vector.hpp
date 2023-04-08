#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iosfwd>
#include <string>

#include "Matrix3.hpp"
#include "Util.hpp"

class Vector {
public:
	Vector() = default;
	Vector(double x, double y, double z);
	explicit Vector(Colour col);

	[[nodiscard]] Vector mult_scalar(double scalar) const;
	[[nodiscard]] double p_norm(double p) const;
	[[nodiscard]] double magnitude() const;
	[[nodiscard]] Vector normalized() const;

	[[nodiscard]] inline double dot(const Vector &vec) const {
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}

	[[nodiscard]] inline double distance(const Vector &vec) const {
		double xd = x - vec.x;
		double yd = y - vec.y;
		double zd = z - vec.z;
		return sqrt(xd * xd + yd * yd + zd * zd);
	}

	[[nodiscard]] double distance_squared(const Vector &vec) const;

	[[nodiscard]] inline Vector map_range(
		const Vector &a_vec, const Vector &b_vec, const Vector &c_vec, const Vector &d_vec) const {
		return Vector(
			Util::map_range(a_vec.x, b_vec.x, c_vec.x, d_vec.x, x),
			Util::map_range(a_vec.y, b_vec.y, c_vec.y, d_vec.y, y),
			Util::map_range(a_vec.z, b_vec.z, c_vec.z, d_vec.z, z));
	};

	[[nodiscard]] Vector round_vec() const;
	[[nodiscard]] Vector rotate_x(double angle_degree) const;
	[[nodiscard]] Vector rotate_y(double angle_degree) const;
	[[nodiscard]] Vector rotate_z(double angle_degree) const;
	[[nodiscard]] Vector rotate_xyz(double x_deg, double y_deg, double z_deg) const;

	[[nodiscard]] Vector operator+(const Vector &vec) const;
	[[nodiscard]] Vector operator+(double scalar) const;

	inline void operator+=(const Vector &vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	void operator*=(double scalar);

	[[nodiscard]] Vector operator-(double scalar) const;

	[[nodiscard]] inline Vector operator-(const Vector &vec) const {
		return {x - vec.x, y - vec.y, z - vec.z};
	}

	[[nodiscard]] Vector operator/(double scalar) const;

	[[nodiscard]] inline Vector operator/(const Vector &vec) {
		return {x / vec.x, y / vec.y, z / vec.z};
	}

	[[nodiscard]] Vector operator*(const Matrix3 &m) const;
	[[nodiscard]] inline Vector operator*(double scalar) const {
		return {x * scalar, y * scalar, z * scalar};
	};

	[[nodiscard]] inline Vector operator*(const Vector &vec) const {
		return {x * vec.x, y * vec.y, z * vec.z};
	}

	inline friend Vector operator*(double lhs, const Vector &rhs) {
		return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
	}

	friend std::ostream &operator<<(std::ostream &strm, const Vector &v);

	[[nodiscard]] Vector operator^(const Vector &vec) const;
	[[nodiscard]] bool operator==(const Vector &vec) const;
	[[nodiscard]] bool operator!=(const Vector &vec) const;

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
};

#endif
