#ifndef CAMERA_MODIFIER
#define CAMERA_MODIFIER

#include "frame_buffer.hpp"

class CameraModifier {
public:
	virtual ~CameraModifier() {}

	virtual void modify(FrameBuffer &buffer) = 0;
};

#endif
