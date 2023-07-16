#pragma once

#include "camera_abs.hpp"
#include "vector.hpp"
#include "util.hpp"
#include "caster.hpp"
#include "settings.hpp"
#include "camera.hpp"

class FrameBuffer;
class StereoCamera: public CameraAbs {
public:
	StereoCamera(Vector eye_position, Vector lookat, Vector up,
		ViewSettings view_settings, Camera *left_camera, 
		Camera *right_camera);
	StereoCamera(const StereoCamera &other);

	~StereoCamera();

	void compute_uvw();
	void setup_camera();
	void render(bool thread);
	void render_highlights(GraphSettings &graph_settings,
		VolumeSettings &volume_settings, std::string image);
	virtual void output(std::string name);

	friend void swap(StereoCamera &first, StereoCamera &second);
	StereoCamera& operator= (StereoCamera other);

	double x_;

protected:
	Camera *left_camera_;
	Camera *right_camera_;

private:
	Vector eye_position_;
	Vector lookat_;
	Vector up_;
	Vector u_;
	Vector v_;
	Vector w_;
	int vp_width_;
	int vp_height_;
	double distance_;
};
