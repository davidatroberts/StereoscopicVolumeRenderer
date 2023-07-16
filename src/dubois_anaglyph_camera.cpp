#include "dubois_anaglyph_camera.hpp"

#include "frame_buffer.hpp"

DuboisAnaglyphCamera::DuboisAnaglyphCamera(
	Vector eye_position, Vector lookat, Vector up, ViewSettings view_settings, Camera *left_camera,
	Camera *right_camera)
	: StereoCamera(eye_position, lookat, up, view_settings, left_camera, right_camera) {}

DuboisAnaglyphCamera::~DuboisAnaglyphCamera() {}

void DuboisAnaglyphCamera::output(std::string name) {
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
			ac.red = (lc.red * 456.0f + lc.green * 500.0f + lc.blue * 176.0f + rc.red * -43.0f + rc.green * -88.0f +
					  rc.blue * -2.0f) /
					 1000.0f;

			// right
			ac.green = (lc.red * -40.0f + lc.green * -38.0f + lc.blue * -16.0f + rc.red * 378.0f + rc.green * 734.0f +
						rc.blue * -18.0f) /
					   1000.0f;

			ac.blue = (lc.red * -15.0f + lc.green * -21.0f + lc.blue * -5.0f + rc.red * -72.0f + rc.green * -113.0f +
					   rc.blue * 1226.0f) /
					  1000.0f;

			// set colour
			anaglyph_buffer(x, y) = ac;
		}
	}

	anaglyph_buffer.output_image("../images/duboisanaglyph_" + name + ".bmp");
}
