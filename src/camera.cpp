#include "camera.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include "caster.hpp"

Camera::Camera(
	Vector eye_position, Vector lookat, Vector up, Caster *caster, FrameBuffer *buffer, ViewSettings view_settings,
	RaySettings ray_settings, double x_offset)
	: CameraAbs(),
	  eye_position_(eye_position),
	  lookat_(lookat),
	  up_(up),
	  vp_width_(view_settings.image_width),
	  vp_height_(view_settings.image_height),
	  distance_(view_settings.distance_to_display_world),
	  caster_(caster),
	  buffer_(buffer),
	  ray_settings_(ray_settings),
	  x_offset(x_offset) {
	fov_ = 2.0 * (atan((vp_height_ / 2) / distance_) * (180.0 / M_PI));

	x_scale = Util::compute_x_scale(300, vp_width_);
	y_scale = Util::compute_y_scale(300, vp_height_);

	aspect_ratio_ = (float)vp_width_ / vp_height_;
	horizontal_fov_ = aspect_ratio_ * fov_;
}

Camera::~Camera() {
	delete buffer_;
}

void Camera::compute_uvw() {
	w_ = eye_position_ - lookat_;
	w_ = w_.normalized();
	u_ = up_ ^ w_;
	u_ = u_.normalized();
	v_ = w_ ^ u_;
}

void Camera::render(bool thread) {
	if (!ray_settings_.sub_sample) {
		if (thread) {
			render_scene_threaded();
		} else {
			render_scene();
		}
	} else {
		render_sub_sample_scene(ray_settings_.subsample_rate);
	}
}

void Camera::render_scene() {
	Vector ray_origin = eye_position_;
	Vector pp;

	for (int y = 0; y < vp_height_; y++) {
		for (int x = 0; x < vp_width_; x++) {
			pp.x = x_scale * (static_cast<double>(x) - 0.5 * (static_cast<double>(vp_width_) - 1.0)) + x_offset;
			pp.y = y_scale * (static_cast<double>(y) - 0.5 * (static_cast<double>(vp_height_) - 1.0));
			const auto ray_dir = ray_direction(pp);

			const auto rgba = caster_->cast(ray_origin, ray_dir);
			(*buffer_)(x, y) = rgba;
		}
	}
}

void Camera::render_sub_sample_scene(int no_over_sample) {
	Vector ray_origin = eye_position_;

	int n = (int)sqrt((float)no_over_sample);
	for (int y = 0; y < vp_height_; y++) {
		for (int x = 0; x < vp_width_; x++) {
			Colour pixel_color = {0, 0, 0, 0};
			for (int p = 0; p < n; ++p) {
				for (int q = 0; q < n; ++q) {
					Vector pp;
					pp.x = x_scale * ((double)x - 0.5 * ((double)vp_width_ - 1.0) + ((q + 0.5) / n)) + x_offset;
					pp.y = y_scale * ((double)y - 0.5 * ((double)vp_height_ - 1.0) + ((p + 0.5) / n));
					Vector ray_dir = ray_direction(pp);

					Colour rgba = caster_->cast(ray_origin, ray_dir);
					rgba.red /= no_over_sample;
					rgba.green /= no_over_sample;
					rgba.blue /= no_over_sample;
					rgba.alpha /= no_over_sample;

					// add to the final pixel colour
					pixel_color.red += rgba.red;
					pixel_color.green += rgba.green;
					pixel_color.blue += rgba.blue;
					pixel_color.alpha += rgba.alpha;
				}
			}
			buffer_->set_pixel(x, y, pixel_color);
		}
	}
}

void Camera::render_scene_threaded() {
	Vector ray_origin = eye_position_;

	// get the number of cores (keep 1 free for OS)
	unsigned int no_threads = std::thread::hardware_concurrency() - 1;

	// split image into regions for each thread
	int tasks = (vp_height_ + no_threads - 1) / no_threads;

	// create threads to run across height
	std::vector<std::thread> threads;
	for (int i = 0; i < no_threads; ++i) {
		threads.push_back(std::thread([this, &ray_origin, tasks, i]() {
			for (int y = (i * tasks); y < ((i + 1) * tasks); ++y) {
				if (y >= vp_height_)
					break;

				// loop through x
				for (int x = 0; x < vp_width_; ++x) {
					// compute direction
					Vector pp;
					pp.x = x_scale * ((double)x - 0.5 * ((double)vp_width_ - 1.0)) + x_offset;
					pp.y = y_scale * ((double)y - 0.5 * ((double)vp_height_ - 1.0));
					Vector ray_dir = ray_direction(pp);

					// cast
					Colour rgba = caster_->cast(ray_origin, ray_dir);
					(*buffer_)(x, y) = rgba;
				}
			}
		}));
	}

	// join the threads back up
	for (auto &t : threads) {
		t.join();
	}
}

void Camera::render_highlights(GraphSettings &graph_settings, VolumeSettings &volume_settings, std::string image_side) {
	if (!graph_settings.highlight_nodes)
		return;

	// get the positions for the pixels for the spheres
	std::vector<Pair> mod_pair_list;
	for (unsigned int i = 0; i < graph_settings.pair_list.size(); ++i) {
		Pair p = graph_settings.pair_list[i];
		determine_highlight_positions(graph_settings, p);
		mod_pair_list.push_back(p);
	}

	// loop through each pair of nodes and copy framebuffer
	for (unsigned int i = 0; i < mod_pair_list.size(); ++i) {
		Pair p = mod_pair_list[i];

		FrameBuffer buffer_copy(*buffer_);
		std::string i_str = std::to_string(i);

		for (unsigned int j = 0; j < p.position_list.size(); ++j) {
			PairFrag pf = p.position_list[j];

			// get the old colour to match opacity
			Colour old_col = buffer_copy.get_pixel(pf.x, pf.y);
			double opacity = (((double)(old_col.red + old_col.green + old_col.blue)) / 3.0f);

			// match the opacity
			opacity /= 255.0f;
			pf.col.red *= opacity;
			pf.col.green *= opacity;
			pf.col.blue *= opacity;

			buffer_copy.set_pixel(pf.x, pf.y, pf.col);
		}
		std::stringstream converter;
		converter << p.linked;

		buffer_copy.output_image(
			"../images/" + image_side + "_" + i_str + "_" + volume_settings.interpolation_str + "_" + converter.str() +
			".bmp");
	}
}

void Camera::output(std::string name) {
	buffer_->output_image("../images/" + name + ".bmp");
}

void Camera::set_eye_position(Vector eye_position) {
	eye_position_ = eye_position;
}

void Camera::set_lookat(Vector lookat) {
	lookat_ = lookat;
}

void Camera::determine_highlight_positions(GraphSettings &graph_settings, Pair &p) {
	Vector ray_origin = eye_position_;

	for (int y = 0; y < vp_height_; ++y) {
		for (int x = 0; x < vp_width_; ++x) {
			Vector pp;
			pp.x = x_scale * ((double)x - 0.5 * ((double)vp_width_ - 1.0)) + x_offset;
			pp.y = y_scale * ((double)y - 0.5 * ((double)vp_height_ - 1.0));
			Vector ray_dir = ray_direction(pp);

			if (caster_->cast_intersect(ray_origin, ray_dir, p)) {
				p.add_position(x, y, graph_settings.highlight_colour);
			}
		}
	}
}
