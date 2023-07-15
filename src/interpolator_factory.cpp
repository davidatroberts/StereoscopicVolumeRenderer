#include "interpolator_factory.hpp"

#include "cc_bspline.hpp"
#include "cc_catmull_rom.hpp"
#include "cc_prefiltered_bspline.hpp"
#include "cc_premultiplied_trilinear.hpp"
#include "cc_trilinear.hpp"
#include "cc_window_sinc.hpp"
#include "window_factory.hpp"

InterpolatorFactory::InterpolatorFactory(Vector min, Vector max) : min_(min), max_(max) {}

Interpolator* InterpolatorFactory::make_interpolator(VolumeSettings volume_settings) {
	switch (volume_settings.interpolation) {
		case InterpolationType::CC_TRILINEAR:
			return new CCTrilinear(min_, max_);
		case InterpolationType::CC_CATMULL:
			return new CCCatmullRom(min_, max_);
		case InterpolationType::CC_INTBSPLINE:
			return new CCPrefilteredBSpline(min_, max_);
		case InterpolationType::CC_BSPLINE:
			return new CCBSpline(min_, max_);
		case InterpolationType::CC_PRETRILINEAR:
			return new CCPremultipliedTrilinear(min_, max_);
		case InterpolationType::CC_WINDOWSINC: {
			// create the window
			WindowFactory window_factory;
			auto window_func = window_factory.make_window(
				volume_settings.window, volume_settings.window_radius, volume_settings.interpolation_settings);

			// create WindowSinc passing in window
			return new CCWindowSinc(min_, max_, volume_settings.window_radius, window_func);
		}
		default:
			return NULL;
			break;
	}
}
