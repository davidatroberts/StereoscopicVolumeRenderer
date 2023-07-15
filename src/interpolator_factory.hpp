#ifndef INTERPOLATOR_FACTORY_H
#define INTERPOLATOR_FACTORY_H

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

#endif