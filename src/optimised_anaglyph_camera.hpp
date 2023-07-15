#ifndef OPTIMISEDANAGLYPH_H
#define OPTIMISEDANAGLYPH_H 

#include "stereo_camera.hpp"
#include "camera.hpp"
#include "vector.hpp"
#include "util.hpp"
#include "caster.hpp"
#include "settings.hpp"

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