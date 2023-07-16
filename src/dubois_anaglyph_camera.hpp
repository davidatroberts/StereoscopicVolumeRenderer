#pragma once

#include "camera.hpp"
#include "caster.hpp"
#include "settings.hpp"
#include "stereo_camera.hpp"
#include "util.hpp"
#include "vector.hpp"

class FrameBuffer;
class DuboisAnaglyphCamera : public StereoCamera {
public:
	DuboisAnaglyphCamera(
		Vector eye_position, Vector lookat, Vector up, ViewSettings view_settings, Camera *left_camera,
		Camera *right_camera);

	~DuboisAnaglyphCamera();

	void output(std::string name);
};
