#pragma once

#include <string>

#include "util.hpp"

class FrameBufferAbs {
public:
	FrameBufferAbs(int width, int height) : width(width), height(height) {}

	virtual ~FrameBufferAbs() {}

	virtual void set_pixel(int x, int y, Colour& rgba) = 0;
	virtual void output_image(std::string file_name) = 0;
	virtual Colour get_pixel(int x, int y) = 0;
	virtual Colour& operator()(int x, int y) = 0;

	int width;
	int height;
};
