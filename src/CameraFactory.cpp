#include "CameraFactory.hpp"

#include "StereoCamera.hpp"
#include "AnaglyphCamera.hpp"
#include "ColourAnaglyphCamera.hpp"
#include "HalfColourAnaglyphCamera.hpp"
#include "OptimisedAnaglyphCamera.hpp"
#include "DuboisAnaglyphCamera.hpp"
#include "CrossEyeCamera.hpp"
#include "FrameBuffer.hpp"

CameraFactory::CameraFactory(Vector eye_position, Vector lookat, Vector up,
	Caster *caster, RaySettings ray_settings)
	: eye_position_(eye_position), lookat_(lookat), up_(up), caster_(caster), 
	ray_settings_(ray_settings) {

}

CameraAbs* CameraFactory::make_camera(ViewSettings view_settings) {
	if (view_settings.camera == CameraType::STEREO) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		StereoCamera *stereo = new StereoCamera(eye_position_, lookat_, up_,
			view_settings, left_camera, right_camera);

		// initiate process
		stereo->compute_uvw();
		stereo->setup_camera();

		return stereo;
	}
	else if (view_settings.camera == CameraType::ANAGLYPH) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		AnaglyphCamera *anaglyph_camera = new AnaglyphCamera(eye_position_, 
			lookat_, up_,view_settings, left_camera, right_camera);

		// initiate process
		anaglyph_camera->compute_uvw();
		anaglyph_camera->setup_camera();

		return anaglyph_camera;
	}
	else if (view_settings.camera == CameraType::COLOUR_ANAGLYPH) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		ColourAnaglyphCamera *anaglyph_camera = new ColourAnaglyphCamera(
			eye_position_, lookat_, up_,
			view_settings, left_camera, right_camera);

		// initiate process
		anaglyph_camera->compute_uvw();
		anaglyph_camera->setup_camera();

		return anaglyph_camera;
	}
	else if (view_settings.camera == CameraType::HALFCOLOUR_ANAGLYPH) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		HalfColourAnaglyphCamera *anaglyph_camera 
			= new HalfColourAnaglyphCamera(eye_position_, lookat_, up_,
			view_settings, left_camera, right_camera);

		// initiate process
		anaglyph_camera->compute_uvw();
		anaglyph_camera->setup_camera();

		return anaglyph_camera;
	}
	else if (view_settings.camera == CameraType::OPTIMISED_ANAGLYPH) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		OptimisedAnaglyphCamera *anaglyph_camera 
			= new OptimisedAnaglyphCamera(eye_position_, lookat_, up_,
			view_settings, left_camera, right_camera);

		// initiate process
		anaglyph_camera->compute_uvw();
		anaglyph_camera->setup_camera();

		return anaglyph_camera;
	}
	else if (view_settings.camera == CameraType::DUBOIS_ANAGLYPH) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		DuboisAnaglyphCamera *anaglyph_camera 
			= new DuboisAnaglyphCamera(eye_position_, lookat_, up_,
			view_settings, left_camera, right_camera);

		// initiate process
		anaglyph_camera->compute_uvw();
		anaglyph_camera->setup_camera();

		return anaglyph_camera;
	}
	else if (view_settings.camera == CameraType::CROSS_EYE) {
		// create the buffers for the stereo camera
		FrameBuffer *left_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);
		FrameBuffer *right_buffer = new FrameBuffer(view_settings.image_width,
			view_settings.image_height);

		// create the two cameras
		Camera *left_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, left_buffer, view_settings, ray_settings_, 0);
		Camera *right_camera = new Camera(eye_position_, lookat_, up_, 
			caster_, right_buffer,view_settings, ray_settings_, 0);

		// create the stereo camera
		CrossEyeCamera *cross_camera 
			= new CrossEyeCamera(eye_position_, lookat_, up_,
			view_settings, left_camera, right_camera);

		// initiate process
		cross_camera->compute_uvw();
		cross_camera->setup_camera();

		return cross_camera;
	}
	else if (view_settings.camera == CameraType::MONO) {
		FrameBuffer *buffer = new FrameBuffer(view_settings.image_width, 
			view_settings.image_height);
		CameraAbs *camera = new Camera(eye_position_, lookat_, up_, caster_,
			buffer, view_settings, ray_settings_, 0);

		// initiate process
		camera->compute_uvw();

		return camera;
	}
	else {
		return NULL;
	}

}