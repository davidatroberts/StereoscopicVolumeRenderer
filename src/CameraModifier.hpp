#ifndef CAMERA_MODIFIER
#define CAMERA_MODIFIER

#include "Framebuffer.hpp"

class CameraModifier {
public:
	virtual ~CameraModifier() {
	}

	virtual void modify(FrameBuffer &buffer) = 0;
};

#endif