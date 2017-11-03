#ifndef OPTIMISEDANAGLYPH_H
#define OPTIMISEDANAGLYPH_H 

#include "StereoCamera.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Util.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

class FrameBuffer;
class OptimisedAnaglyphCamera: public StereoCamera {
public:
	OptimisedAnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera, 
		Camera *right_camera);

	~OptimisedAnaglyphCamera();

	void output(std::string name);
};

#endif