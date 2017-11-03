#ifndef INTERPOLATOR_FACTORY_H
#define INTERPOLATOR_FACTORY_H

#include "Vector.hpp"
#include "Interpolator.hpp"
#include "Settings.hpp"

class InterpolatorFactory {
public:
	InterpolatorFactory(Vector min, Vector max);

	Interpolator* make_interpolator(VolumeSettings volume_settings);

private:
	Vector min_;
	Vector max_;
};

#endif