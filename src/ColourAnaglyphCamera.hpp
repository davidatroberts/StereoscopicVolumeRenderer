#ifndef COLOURANAGLYPH_H
#define COLOURANAGLYPH_H

#include "StereoCamera.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Util.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

class FrameBuffer;
class ColourAnaglyphCamera: public StereoCamera {
public:
	ColourAnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera, 
		Camera *right_camera);

	~ColourAnaglyphCamera();

	void output(std::string name);
};

#endif