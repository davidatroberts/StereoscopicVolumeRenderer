#ifndef POINT_MODIFIER_FACTORY
#define POINT_MODIFIER_FACTORY

#include "settings.hpp"
#include "point_modifier.hpp"

class PointModifierFactory {
public:
	PointModifierFactory();

	PointModifier* make_modifier(PointModifierSettings &settings, 
		RaySettings ray_settings, VolumeSettings volume_settings);
};

#endif