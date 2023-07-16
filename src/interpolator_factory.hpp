#pragma once

#include "vector.hpp"
#include "interpolator.hpp"
#include "settings.hpp"

class InterpolatorFactory {
public:
	InterpolatorFactory(Vector min, Vector max);

	Interpolator* make_interpolator(VolumeSettings volume_settings);

private:
	Vector min_;
	Vector max_;
};
