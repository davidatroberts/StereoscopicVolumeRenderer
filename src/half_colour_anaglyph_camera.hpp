#pragma once

#include "stereo_camera.hpp"
#include "camera.hpp"
#include "vector.hpp"
#include "util.hpp"
#include "caster.hpp"
#include "settings.hpp"

class FrameBuffer;
class HalfColourAnaglyphCamera: public StereoCamera {
public:
	HalfColourAnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera, 
		Camera *right_camera);

	~HalfColourAnaglyphCamera();

	void output(std::string name);
};
