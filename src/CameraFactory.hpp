#ifndef CAMERA_FACTORY_H
#define CAMERA_FACTORY_H

#include "Vector.hpp"
#include "CameraAbs.hpp"
#include "Camera.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

class CameraFactory {
public:
	CameraFactory(Vector eye_position, Vector lookat, Vector up,
		Caster *caster, RaySettings ray_settings);

	CameraAbs* make_camera(ViewSettings view_settings);

private:
	Vector eye_position_;
	Vector lookat_;
	Vector up_;
	Caster *caster_;
	RaySettings ray_settings_;
};

#endif