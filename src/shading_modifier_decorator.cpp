#include "shading_modifier_decorator.hpp"

#include "gradient_factory.hpp"
#include "illumination_model_factory.hpp"

ShadingModifierDecorator::ShadingModifierDecorator(
    PointModifier *basic_modifier, picojson::value::object &settings_obj,
    RaySettings ray_settings, VolumeSettings volume_settings)
    : basic_modifier_(basic_modifier),
      ray_settings_(ray_settings),
      volume_settings_(volume_settings) {
  // read the settings for the shader
  shader_settings_ = Settings::read_shader_settings(settings_obj);

  // get the illumination funciton
  illumination_ =
      IlluminationModelFactory::make_model(shader_settings_.illumination_model);

  // get the gradient function
  gradient_ = GradientFactory::make_gradient(shader_settings_.gradient,
                                             volume_settings_.resolution);
}

ShadingModifierDecorator::ShadingModifierDecorator(
    const ShadingModifierDecorator &other)
    : basic_modifier_(other.basic_modifier_),
      ray_settings_(other.ray_settings_),
      volume_settings_(other.volume_settings_) {}

ShadingModifierDecorator::~ShadingModifierDecorator() {}

void ShadingModifierDecorator::modify(Matrix3D &mat,
                                      const Vector &ray_direction,
                                      const Vector &ray_position,
                                      Vector4 &src_rgba) {
  basic_modifier_->modify(mat, ray_direction, ray_position, src_rgba);

  // get the normal for the boundary
  Vector normal = gradient_(mat, ray_position);

  // calculate the light direction
  Vector light_direction = ray_position - shader_settings_.light_position;
  light_direction = light_direction.normalized();

  // compute the shading
  Vector shade = illumination_(
      normal, ray_direction, light_direction, shader_settings_.ka,
      shader_settings_.kd, shader_settings_.ks, shader_settings_.n,
      shader_settings_.light_colour, shader_settings_.ambient_colour);

  // set the colours
  src_rgba.x = shade.x;
  src_rgba.y = shade.y;
  src_rgba.z = shade.z;
}

void swap(ShadingModifierDecorator &first, ShadingModifierDecorator &second) {
  using std::swap;
  swap(first.basic_modifier_, second.basic_modifier_);
  swap(first.ray_settings_, second.ray_settings_);
  swap(first.volume_settings_, second.volume_settings_);
}

ShadingModifierDecorator &ShadingModifierDecorator::operator=(
    ShadingModifierDecorator other) {
  swap(*this, other);
  return *this;
}
