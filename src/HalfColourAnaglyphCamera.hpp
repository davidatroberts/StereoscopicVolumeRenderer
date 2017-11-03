#ifndef HALFCOLURANAGLYPH_H
#define HALFCOLURANAGLYPH_H

#include "StereoCamera.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Util.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

class FrameBuffer;
class HalfColourAnaglyphCamera: public StereoCamera {
public:
	HalfColourAnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera, 
		Camera *right_camera);

	~HalfColourAnaglyphCamera();

	void output(std::string name);
};

#endif