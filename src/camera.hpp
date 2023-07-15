#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include "camera_abs.hpp"
#include "caster.hpp"
#include "frame_buffer.hpp"
#include "settings.hpp"
#include "util.hpp"
#include "vector.hpp"

class Camera : public CameraAbs {
public:
	Camera(
		Vector eye_position, Vector lookat, Vector up, Caster *caster, FrameBuffer *buffer, ViewSettings view_settings,
		RaySettings ray_settings, double x_offset);

	virtual ~Camera();

	void compute_uvw();
	void set_eye_position(Vector eye_position);
	void set_lookat(Vector lookat);

	virtual void render(bool thread);
	virtual void render_scene();
	virtual void render_sub_sample_scene(int samples_per_pixel);
	virtual void render_scene_threaded();
	virtual void render_highlights(
		GraphSettings &graph_settings, VolumeSettings &volume_settings, std::string image_side);
	virtual void output(std::string name);

	inline Vector ray_direction(const Vector &p) const {
		return (u_ * p.x + v_ * p.y - w_ * distance_).normalized();
	};

	double x_offset;
	FrameBuffer *buffer_;

protected:
	int vp_width_;
	int vp_height_;

	double distance_;
	double fov_;
	double horizontal_fov_;
	double aspect_ratio_;
	double x_scale;
	double y_scale;

	Vector eye_position_;
	Vector lookat_;
	Vector up_;
	Vector u_;
	Vector v_;
	Vector w_;
	Caster *caster_;
	RaySettings ray_settings_;

private:
	void determine_highlight_positions(GraphSettings &graph_settings, Pair &p);
};

#endif
