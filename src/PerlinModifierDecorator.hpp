#ifndef PERLIN_MODIFIER_DECORATOR
#define PERLIN_MODIFIER_DECORATOR

#include "CCLattice.hpp"
#include "CCTrilinear.hpp"
#include "PointModifier.hpp"
#include "Settings.hpp"
#include "picojson.h"
#include "simplex.hpp"

class PerlinModifierDecorator : public PointModifier {
 public:
  PerlinModifierDecorator(PointModifier *basic_modifer,
                          picojson::value::object &settings_obj,
                          RaySettings ray_settings,
                          VolumeSettings volume_settings);
  PerlinModifierDecorator(const PerlinModifierDecorator &other);

  ~PerlinModifierDecorator();

  void modify(Matrix3D &mat, const Vector &ray_direction,
              const Vector &ray_position, Vector4 &src_rgba);

  friend void swap(PerlinModifierDecorator &first,
                   PerlinModifierDecorator &second);
  PerlinModifierDecorator &operator=(PerlinModifierDecorator other);

 private:
  PointModifier *basic_modifier_;
  CCLattice *perlin_volume_;
  RaySettings ray_settings_;
  VolumeSettings volume_settings_;
  int multiplier_;
};

#endif
