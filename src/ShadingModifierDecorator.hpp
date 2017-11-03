#ifndef SHADING_MODIFIER_DECORATOR
#define SHADING_MODIFIER_DECORATOR

#include <functional>
#include "Matrix3D.hpp"
#include "PointModifier.hpp"
#include "picojson.h"
#include "Settings.hpp"

class ShadingModifierDecorator: public PointModifier {
public:
	ShadingModifierDecorator(PointModifier *basic_modifer, 
		picojson::value::object &settings_obj, RaySettings ray_settings,
		VolumeSettings volume_settings);
	ShadingModifierDecorator(const ShadingModifierDecorator &other);

	~ShadingModifierDecorator();

	void modify(Matrix3D &mat, Vector &ray_direction, Vector &ray_position, Vector4 &src_rgba);

	friend void swap(ShadingModifierDecorator& first, 
		ShadingModifierDecorator &second);
	ShadingModifierDecorator& operator= (ShadingModifierDecorator other);

private:
	PointModifier *basic_modifier_;
	RaySettings ray_settings_;
	VolumeSettings volume_settings_;
	ShaderSettings shader_settings_;
	std::function<Vector(Vector, Vector, Vector, Vector, Vector, 
		Vector, double, Vector, Vector)> illumination_;
	std::function<Vector(Matrix3D &mat, Vector)> gradient_;
};

#endif