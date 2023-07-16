#pragma once

#include "camera_modifier.hpp"
#include "frame_buffer.hpp"

class NullCameraModifier: public CameraModifier {
public:
	~NullCameraModifier();

	void modify(FrameBuffer &buffer);
};
