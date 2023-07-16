#include "colour_anaglyph_camera.hpp"

#include "frame_buffer.hpp"

ColourAnaglyphCamera::ColourAnaglyphCamera(
	Vector eye_position, Vector lookat, Vector up, ViewSettings view_settings, Camera *left_camera,
	Camera *right_camera)
	: StereoCamera(eye_position, lookat, up, view_settings, left_camera, right_camera) {}

ColourAnaglyphCamera::~ColourAnaglyphCamera() {}

void ColourAnaglyphCamera::output(std::string name) {
	// get the width and height of image
	int width = left_camera_->buffer_->width;
	int height = left_camera_->buffer_->height;

	// initialize anaglyph buffer
	FrameBuffer anaglyph_buffer(width, height);

	// iterate through the buffers and adjust for Colour Anaglyph
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			// get the colours from left and right camera
			Colour lc = (*left_camera_->buffer_)(x, y);
			Colour rc = (*right_camera_->buffer_)(x, y);

			// combined colour
			Colour ac;

			// left
			ac.red = lc.red;

			// right
			ac.green = rc.green;
			ac.blue = rc.blue;

			// set colour
			anaglyph_buffer(x, y) = ac;
		}
	}

	anaglyph_buffer.output_image("../images/colouranaglyph_" + name + ".bmp");
}
