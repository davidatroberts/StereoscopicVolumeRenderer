#pragma once

#include "matrix_3d.hpp"
#include "vector.hpp"
#include "vector4.hpp"

class PointModifier {
 public:
  virtual ~PointModifier() {}

  virtual void modify(Matrix3D &mat, const Vector &ray_direction,
                      const Vector &ray_position, Vector4 &src_rgba) = 0;
};
