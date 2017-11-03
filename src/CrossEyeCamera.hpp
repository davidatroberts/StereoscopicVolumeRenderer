#ifndef CROSS_EYE_CAMERA
#define CROSS_EYE_CAMERA 

#include "StereoCamera.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Util.hpp"
#include "Caster.hpp"
#include "Settings.hpp"

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