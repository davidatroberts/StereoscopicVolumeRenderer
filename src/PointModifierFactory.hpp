#ifndef POINT_MODIFIER_FACTORY
#define POINT_MODIFIER_FACTORY

#include "Settings.hpp"
#include "PointModifier.hpp"

class PointModifierFactory {
public:
	PointModifierFactory();

	PointModifier* make_modifier(PointModifierSettings &settings, 
		RaySettings ray_settings, VolumeSettings volume_settings);
};

#endif