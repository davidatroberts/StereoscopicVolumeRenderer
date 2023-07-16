#pragma once

#include <picojson.h>

#include <functional>

#include "matrix_3d.hpp"
#include "point_modifier.hpp"
#include "settings.hpp"

class ShadingModifierDecorator : public PointModifier {
public:
	ShadingModifierDecorator(
		PointModifier *basic_modifer, picojson::value::object &settings_obj, RaySettings ray_settings,
		VolumeSettings volume_settings);
	ShadingModifierDecorator(const ShadingModifierDecorator &other);

	~ShadingModifierDecorator();

	void modify(Matrix3D &mat, const Vector &ray_direction, const Vector &ray_position, Vector4 &src_rgba);

	friend void swap(ShadingModifierDecorator &first, ShadingModifierDecorator &second);
	ShadingModifierDecorator &operator=(ShadingModifierDecorator other);

private:
	PointModifier *basic_modifier_;
	RaySettings ray_settings_;
	VolumeSettings volume_settings_;
	ShaderSettings shader_settings_;
	std::function<Vector(Vector, Vector, Vector, Vector, Vector, Vector, double, Vector, Vector)> illumination_;
	std::function<Vector(Matrix3D &mat, Vector)> gradient_;
};
