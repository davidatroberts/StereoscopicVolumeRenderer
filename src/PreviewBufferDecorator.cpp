#include "PreviewBufferDecorator.hpp"

PreviewBufferDecorator::PreviewBufferDecorator(FrameBufferAbs *buffer)
:FrameBufferAbs(buffer->width, buffer->height), buffer_(buffer) {

}

PreviewBufferDecorator::PreviewBufferDecorator(
	const PreviewBufferDecorator &other):
	FrameBufferAbs(other.width, other.height), buffer_(other.buffer_) {

}

PreviewBufferDecorator::~PreviewBufferDecorator() {
	delete buffer_;
}

void PreviewBufferDecorator::set_pixel(int x, int y, Colour &rgba) {
	buffer_->set_pixel(x, y, rgba);
}

void PreviewBufferDecorator::output_image(std::string file_name) {
	buffer_->output_image(file_name);
}

Colour PreviewBufferDecorator::get_pixel(int x, int y) {
	return buffer_->get_pixel(x, y);
}

Colour& PreviewBufferDecorator::operator()(int x, int y) {
	return (*buffer_)(x, y);
}

void swap(PreviewBufferDecorator &first, PreviewBufferDecorator &second) {
	using std::swap;
	swap(first.buffer_, second.buffer_);
	swap(first.width, second.width);
	swap(first.height, second.height);
}

PreviewBufferDecorator& PreviewBufferDecorator::operator= (
	PreviewBufferDecorator other) {
	swap(*this, other);
	return *this;
}