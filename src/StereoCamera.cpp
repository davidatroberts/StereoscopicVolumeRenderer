#include "StereoCamera.hpp"

#include <cmath>

#include "Camera.hpp"
#include "Framebuffer.hpp"

StereoCamera::StereoCamera(Vector eye_position, Vector lookat, Vector up,
	ViewSettings view_settings, Camera *left_camera, Camera *right_camera)
: CameraAbs(), eye_position_(eye_position), lookat_(lookat), up_(up), 
distance_(view_settings.distance_to_display_world), 
vp_width_(view_settings.image_width), vp_height_(view_settings.image_height),
left_camera_(left_camera), right_camera_(right_camera) {
	x_ = view_settings.IOD_world/2.0f;
	left_camera_->x_offset = x_;
	right_camera_->x_offset = -x_;
}

StereoCamera::StereoCamera(const StereoCamera &other)
: eye_position_(other.eye_position_), lookat_(other.lookat_), up_(other.up_),
distance_(other.distance_), vp_width_(other.vp_width_), 
vp_height_(other.vp_height_), left_camera_(other.left_camera_), 
right_camera_(other.right_camera_), x_(other.x_) {

}

StereoCamera::~StereoCamera() {
	delete left_camera_;
	delete right_camera_;
}

void StereoCamera::compute_uvw() {
	w_ = eye_position_ - lookat_;
	w_ = w_.normalized();
	u_ = up_ ^ w_;
	u_ = u_.normalized();
	v_ = w_ ^ u_;
}

void StereoCamera::setup_camera() {
	Vector left_eye = eye_position_ - u_.mult_scalar(x_);
	Vector left_lookat = lookat_ - u_.mult_scalar(x_);
	left_camera_->set_eye_position(left_eye);
	left_camera_->set_lookat(left_lookat);
	left_camera_->compute_uvw();

	Vector right_eye = eye_position_ + u_.mult_scalar(x_);
	Vector right_lookat = lookat_ + u_.mult_scalar(x_);

	right_camera_->set_eye_position(right_eye);
	right_camera_->set_lookat(right_lookat);
	right_camera_->compute_uvw();
}

void StereoCamera::render(bool thread) {
	left_camera_->render(thread);
	right_camera_->render(thread);
}

void StereoCamera::render_highlights(GraphSettings &graph_settings,
	VolumeSettings &volume_settings, std::string image) {
	left_camera_->render_highlights(graph_settings, volume_settings, "left");
	right_camera_->render_highlights(graph_settings, volume_settings, "right");
}

void StereoCamera::output(std::string name) {
	left_camera_->output("left_"+name);
	right_camera_->output("right_"+name);
}

void swap(StereoCamera &first, StereoCamera &second) {
	using std::swap;
	swap(first.eye_position_, second.eye_position_);
	swap(first.lookat_, second.lookat_);
	swap(first.up_, second.up_);
	swap(first.distance_, second.distance_);
	swap(first.vp_width_, second.vp_width_);
	swap(first.vp_height_, second.vp_height_);
	swap(first.left_camera_, second.left_camera_);
	swap(first.right_camera_, second.right_camera_);
	swap(first.x_, second.x_);
}	

StereoCamera& StereoCamera::operator= (StereoCamera other) {
	swap(*this, other);
	return *this;
}