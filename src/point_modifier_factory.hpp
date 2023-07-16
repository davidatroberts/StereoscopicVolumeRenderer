#pragma once

#include "point_modifier.hpp"
#include "settings.hpp"

class PointModifierFactory {
public:
	PointModifierFactory();

	PointModifier* make_modifier(
		PointModifierSettings& settings, RaySettings ray_settings, VolumeSettings volume_settings);
};
