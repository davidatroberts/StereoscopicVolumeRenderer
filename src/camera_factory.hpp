#pragma once

#include "camera.hpp"
#include "camera_abs.hpp"
#include "caster.hpp"
#include "settings.hpp"
#include "vector.hpp"

class CameraFactory {
public:
	CameraFactory(Vector eye_position, Vector lookat, Vector up, Caster *caster, RaySettings ray_settings);

	CameraAbs *make_camera(ViewSettings view_settings);

private:
	Vector eye_position_;
	Vector lookat_;
	Vector up_;
	Caster *caster_;
	RaySettings ray_settings_;
};
