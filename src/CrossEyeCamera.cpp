#include "CrossEyeCamera.hpp"

#include "FrameBuffer.hpp"

CrossEyeCamera::CrossEyeCamera(Vector eye_position, Vector lookat, Vector up,
	ViewSettings view_settings, Camera *left_camera, Camera *right_camera)
:StereoCamera(eye_position, lookat, up, view_settings, left_camera, right_camera) {
}

CrossEyeCamera::~CrossEyeCamera() {
}

void CrossEyeCamera::output(std::string name) {
	// get the width and height of image
	int width = left_camera_->buffer_->width;
	int height = left_camera_->buffer_->height;

	// initialize crosseyed buffer
	FrameBuffer cross_buffer((width*2)+10, height);

	// put the images in the correct place
	for (int x=0; x<width; ++x) {
		for (int y=0; y<width; ++y) {
			// get the colours from left and right camera
			Colour lc = (*left_camera_->buffer_)(x, y);
			Colour rc = (*right_camera_->buffer_)(x, y);

			cross_buffer(x, y) = rc;
			cross_buffer(x+width+10, y) = lc;
		}
	}

	cross_buffer.output_image("../images/cross_"+name+".bmp");
}