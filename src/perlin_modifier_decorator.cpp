#include "perlin_modifier_decorator.hpp"

#include <stdlib.h>
#include <time.h>

#include "interpolator_factory.hpp"
#include "matrix_3d.hpp"

#define BASE_SAMPLING_STEP 0.015625

PerlinModifierDecorator::PerlinModifierDecorator(
	PointModifier *basic_modifier, picojson::value::object &settings_obj, RaySettings ray_settings,
	VolumeSettings volume_settings)
	: basic_modifier_(basic_modifier), ray_settings_(ray_settings), volume_settings_(volume_settings) {
	multiplier_ = (int)settings_obj["multiplier"].get<double>();

	// seed random number generator
	srand(time(NULL));

	// initiate the perlin volume
	Matrix3D perlin_mat(256, 256, 256);
	for (int z = 0; z < 256; ++z) {
		for (int y = 0; y < 256; ++y) {
			for (int x = 0; x < 256; ++x) {
				float perl = scaled_raw_noise_3d(0.0f, multiplier_, x, y, z);
				perlin_mat(x, y, z) = perl;
			}
		}
	}

	// load the interpolator
	InterpolatorFactory interpolator_factory(Vector(0, 0, 0), Vector(256, 256, 256));
	Interpolator *interpolator = interpolator_factory.make_interpolator(volume_settings_);

	// initiate the lattice to store the perlin volume
	perlin_volume_ = new CCLattice(Vector(0, 0, 0), Vector(1, 1, 1), Vector(256, 256, 256), interpolator);
	perlin_volume_->load(perlin_mat);

	// run any preprocessing required for the interpolator
	interpolator->preprocess(perlin_volume_->raw_data());
}

PerlinModifierDecorator::PerlinModifierDecorator(const PerlinModifierDecorator &other)
	: basic_modifier_(other.basic_modifier_),
	  perlin_volume_(other.perlin_volume_),
	  ray_settings_(other.ray_settings_),
	  volume_settings_(other.volume_settings_),
	  multiplier_(other.multiplier_) {}

PerlinModifierDecorator::~PerlinModifierDecorator() {
	delete basic_modifier_;
	delete perlin_volume_;
}

void PerlinModifierDecorator::modify(
	Matrix3D &mat, const Vector &ray_direction, const Vector &ray_position, Vector4 &src_rgba) {
	basic_modifier_->modify(mat, ray_direction, ray_position, src_rgba);

	// sample the perlin volume
	// this modifies the attenuation coefficient
	src_rgba.w = src_rgba.w * perlin_volume_->intersect(ray_position);
}

void swap(PerlinModifierDecorator &first, PerlinModifierDecorator &second) {
	using std::swap;
	swap(first.basic_modifier_, second.basic_modifier_);
	swap(first.perlin_volume_, second.perlin_volume_);
	swap(first.multiplier_, second.multiplier_);
	swap(first.ray_settings_, second.ray_settings_);
	swap(first.volume_settings_, second.volume_settings_);
}

PerlinModifierDecorator &PerlinModifierDecorator::operator=(PerlinModifierDecorator other) {
	swap(*this, other);
	return *this;
}
