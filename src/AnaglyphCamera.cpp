#include "AnaglyphCamera.hpp"

#include "FrameBuffer.hpp"

AnaglyphCamera::AnaglyphCamera(Vector eye_position, Vector lookat, Vector up,
	ViewSettings view_settings, Camera *left_camera, Camera *right_camera)
:StereoCamera(eye_position, lookat, up, view_settings, left_camera, right_camera) {

}

AnaglyphCamera::~AnaglyphCamera() {

}

void AnaglyphCamera::output(std::string name) {
	// get the width and height of image
	int width = left_camera_->buffer_->width;
	int height = left_camera_->buffer_->height;

	// initialize anaglyph buffer
	FrameBuffer anaglyph_buffer(width, height);

	// iterate through the buffers and adjust to set for red / cyan
	for (int x=0; x<width; ++x) {
		for (int y=0; y<height; ++y) {
			// get the colours from left and right camera
			Colour lc = (*left_camera_->buffer_)(x, y);
			Colour rc = (*right_camera_->buffer_)(x, y);

			// combined colour
			Colour ac;
		
			ac.red = 0.299f*lc.red + 0.587f*lc.green + 0.114f*lc.blue;
			ac.green = 0.299f*rc.red + 0.587f*rc.green + 0.114f*rc.blue;
			ac.blue = 0.299f*rc.red + 0.587f*rc.green + 0.114f*rc.blue;

			anaglyph_buffer(x, y) = ac;
		}
	}

	anaglyph_buffer.output_image("../images/anaglyph_"+name+".bmp");
}