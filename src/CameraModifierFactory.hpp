#ifndef CAMERA_MODIFIER_FACTORY
#define CAMERA_MODIFIER_FACTORY

#include "Settings.hpp"
#include "CameraModifier.hpp"

class CameraModifierFactory {
public:
	CameraModifierFactory();

	CameraModifier* make_modifier(CameraModifierSettings &settings,
		ViewSettings view_settings);
};

#endif