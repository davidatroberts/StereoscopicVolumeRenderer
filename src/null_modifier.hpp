#pragma once

#include "point_modifier.hpp"

class NullModifier : public PointModifier {
 public:
  ~NullModifier();

  void modify(Matrix3D &mat, const Vector &ray_direction,
              const Vector &ray_position, Vector4 &src_rgba);
};
