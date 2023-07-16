#pragma once

#include <string>

#include "frame_buffer_abs.hpp"
#include "util.hpp"

class FrameBuffer : public FrameBufferAbs {
public:
	FrameBuffer(int width = 300, int height = 300);
	FrameBuffer(const FrameBuffer &other);

	~FrameBuffer();

	void set_pixel(int x, int y, Colour &rgba);
	void output_image(std::string fname);

	Colour get_pixel(int x, int y);
	Colour &operator()(int x, int y);

	friend void swap(FrameBuffer &first, FrameBuffer &second);
	FrameBuffer &operator=(FrameBuffer other);

private:
	Colour *img_;
};
