#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <ostream>
#include <string>

#include "Matrix3.hpp"
#include "Util.hpp"

class Vector {
 public:
  Vector(double x = 0, double y = 0, double z = 0);
  Vector(Colour col);

  Vector mult_scalar(double scalar) const;
  double p_norm(double p) const;
  double magnitude() const;
  Vector normalized() const;

  inline double dot(const Vector &vec) const {
    return (x * vec.x) + (y * vec.y) + (z * vec.z);
  }

  inline double distance(const Vector &vec) const {
    double xd = x - vec.x;
    double yd = y - vec.y;
    double zd = z - vec.z;
    return sqrt(xd * xd + yd * yd + zd * zd);
  }

  double distance_squared(const Vector &vec) const;

  inline Vector map_range(const Vector &a_vec, const Vector &b_vec,
                          const Vector &c_vec, const Vector &d_vec) const {
    return Vector(Util::map_range(a_vec.x, b_vec.x, c_vec.x, d_vec.x, x),
                  Util::map_range(a_vec.y, b_vec.y, c_vec.y, d_vec.y, y),
                  Util::map_range(a_vec.z, b_vec.z, c_vec.z, d_vec.z, z));
  };

  Vector round_vec() const;
  Vector rotate_x(double angle_degree) const;
  Vector rotate_y(double angle_degree) const;
  Vector rotate_z(double angle_degree) const;
  Vector rotate_xyz(double x_deg, double y_deg, double z_deg) const;

  Vector operator+(const Vector &vec) const;
  Vector operator+(double scalar) const;

  inline void operator+=(const Vector &vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
  }

  void operator*=(double scalar);

  Vector operator-(double scalar) const;

  inline Vector operator-(const Vector &vec) const {
    return Vector(x - vec.x, y - vec.y, z - vec.z);
  }

  Vector operator/(double scalar);

  inline Vector operator/(const Vector &vec) {
    return Vector(x / vec.x, y / vec.y, z / vec.z);
  }

  Vector operator*(Matrix3 &m) const;
  inline Vector operator*(double scalar) const {
    return Vector(x * scalar, y * scalar, z * scalar);
  };

  inline Vector operator*(const Vector &vec) const {
    return Vector(x * vec.x, y * vec.y, z * vec.z);
  }

  inline friend Vector operator*(double lhs, const Vector &rhs) {
    return Vector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
  }

  friend std::ostream &operator<<(std::ostream &strm, Vector &v);

  Vector operator^(const Vector &vec);
  bool operator==(const Vector &vec) const;
  bool operator!=(const Vector &vec);

  double x;
  double y;
  double z;
};

#endif
