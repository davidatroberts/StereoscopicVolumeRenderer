#pragma once

#include "camera_modifier.hpp"
#include "settings.hpp"

class CameraModifierFactory {
public:
	CameraModifierFactory();

	CameraModifier* make_modifier(CameraModifierSettings& settings, ViewSettings view_settings);
};
