#pragma once

#include "interpolator.hpp"
#include "settings.hpp"
#include "vector.hpp"

class InterpolatorFactory {
public:
	InterpolatorFactory(Vector min, Vector max);

	Interpolator* make_interpolator(VolumeSettings volume_settings);

private:
	Vector min_;
	Vector max_;
};
