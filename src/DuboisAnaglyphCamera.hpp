#ifndef DUBOISANAGLYPH_H
#define DUBOISANAGLYPH_H 

#include "StereoCamera.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Util.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

class FrameBuffer;
class DuboisAnaglyphCamera: public StereoCamera {
public:
	DuboisAnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera, 
		Camera *right_camera);

	~DuboisAnaglyphCamera();

	void output(std::string name);
};

#endif