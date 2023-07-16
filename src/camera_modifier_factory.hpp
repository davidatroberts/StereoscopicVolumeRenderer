#pragma once

#include "settings.hpp"
#include "camera_modifier.hpp"

class CameraModifierFactory {
public:
	CameraModifierFactory();

	CameraModifier* make_modifier(CameraModifierSettings &settings,
		ViewSettings view_settings);
};
