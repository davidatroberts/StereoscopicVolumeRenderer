#ifndef NULL_CAMERA_MODIFIER
#define NULL_CAMERA_MODIFIER

#include "CameraModifier.hpp"
#include "FrameBuffer.hpp"

class NullCameraModifier: public CameraModifier {
public:
	~NullCameraModifier();

	void modify(FrameBuffer &buffer);
};

#endif