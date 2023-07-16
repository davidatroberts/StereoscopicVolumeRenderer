#pragma once

#include "frame_buffer.hpp"

class CameraModifier {
public:
	virtual ~CameraModifier() {}

	virtual void modify(FrameBuffer &buffer) = 0;
};
