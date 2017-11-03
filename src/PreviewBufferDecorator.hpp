#ifndef PREVIEW_BUFFER_DECORATOR
#define PREVIEW_BUFFER_DECORATOR

#include "FrameBufferAbs.hpp"
#include "Util.hpp"

class PreviewBufferDecorator: public FrameBufferAbs {
public:
	PreviewBufferDecorator(FrameBufferAbs *buffer);
	PreviewBufferDecorator(const PreviewBufferDecorator &other);

	~PreviewBufferDecorator();

	void set_pixel(int x, int y, Colour &rgba);
	void output_image(std::string file_name);

	Colour get_pixel(int x, int y);
	Colour& operator()(int x, int y);

	friend void swap(PreviewBufferDecorator &first, 
		PreviewBufferDecorator &second);
	PreviewBufferDecorator& operator= (PreviewBufferDecorator other);

private:
	FrameBufferAbs *buffer_;
};

#endif