#include "FrameBuffer.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

#define cimg_display 0
#include <CImg.h>
using namespace cimg_library;

FrameBuffer::FrameBuffer(int width, int height)
: FrameBufferAbs(width, height), img_(new Colour[width*height])  {
}

FrameBuffer::FrameBuffer(const FrameBuffer &other)
:FrameBufferAbs(other.width, other.height), 
img_(new Colour[other.width*other.height]) {
	std::copy(other.img_, other.img_ + (other.width*other.height), img_);
}

FrameBuffer::~FrameBuffer() {
	delete[] img_;
}

void FrameBuffer::set_pixel(int x, int y, Colour &rgba) {
	img_[x*height+y] = rgba;
}

void FrameBuffer::output_image(std::string fname) {
	CImg<float> img(width, height, 1, 3);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x<width; x++) {
			const float colour[] = {
				float(img_[x*height+y].red), 
				float(img_[x*height+y].green), 
				float(img_[x*height+y].blue), 
				255
			};
			img.draw_point(x, height-y, colour);
		}
	}

	img.save_bmp(fname.c_str());
}

Colour FrameBuffer::get_pixel(int x, int y) {
	return img_[x*height+y];
}

Colour& FrameBuffer::operator()(int x, int y) {
	return img_[x*height+y];
}

void swap(FrameBuffer &first, FrameBuffer &second) {
	using std::swap;
	swap(first.width, second.width);
	swap(first.height, second.height);
	swap(first.img_, second.img_);
}

FrameBuffer& FrameBuffer::operator= (FrameBuffer other) {
	swap(*this, other);
	return *this;
}