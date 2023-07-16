#pragma once

#include "settings.hpp"
#include "point_modifier.hpp"

class PointModifierFactory {
public:
	PointModifierFactory();

	PointModifier* make_modifier(PointModifierSettings &settings, 
		RaySettings ray_settings, VolumeSettings volume_settings);
};
