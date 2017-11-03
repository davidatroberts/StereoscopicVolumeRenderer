#ifndef ANAGLYPH_CAMERA_H
#define ANAGLYPH_CAMERA_H

#include "StereoCamera.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Util.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

class FrameBuffer;
class AnaglyphCamera: public StereoCamera {
public:
	AnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera,
		Camera*right_camera);

	~AnaglyphCamera();

	void output(std::string name);
};

#endif