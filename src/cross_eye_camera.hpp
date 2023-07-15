#ifndef CROSS_EYE_CAMERA
#define CROSS_EYE_CAMERA 

#include "stereo_camera.hpp"
#include "camera.hpp"
#include "vector.hpp"
#include "util.hpp"
#include "caster.hpp"
#include "settings.hpp"

class FrameBuffer;
class CrossEyeCamera: public StereoCamera {
public:
	CrossEyeCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera,
		Camera*right_camera);

	~CrossEyeCamera();

	void output(std::string name);
};

#endif