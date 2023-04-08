#include "CCWindowSinc.hpp"

#include <math.h>

#include <functional>

CCWindowSinc::CCWindowSinc(Vector min, Vector max, int radius, std::function<double(double)> window_func)
	: CCInterpolator(min, max), radius_(radius), window_m_(radius_ * 2), window_func_(window_func) {}

CCWindowSinc::~CCWindowSinc() {}

void CCWindowSinc::preprocess(Matrix3D &mat) {
	return;
}

double CCWindowSinc::interpolate(const Vector &position, const Matrix3D &mat) const {
	// compute the integer index based on the floored one
	int xi = floor(position.x);
	int yi = floor(position.y);
	int zi = floor(position.z);

	// compute the distance to next index (fractional)
	double xd = position.x - xi;
	double yd = position.y - yi;
	double zd = position.z - zi;

	// weights dimensions
	double weight_x[2 * radius_];
	double weight_y[2 * radius_];
	double weight_z[2 * radius_];

	// compute the offset for x (parameter of the kernel)
	double x_offset = xd + radius_;
	double y_offset = yd + radius_;
	double z_offset = zd + radius_;

	// compute the sinc function for x,y,z separately
	if (xd == 0.0) {  // lies on grid lattice
		for (int i = 0; i < window_m_; ++i) {
			weight_x[i] = static_cast<int>(i) == radius_ - 1 ? 1 : 0;
		}
	} else {
		for (int i = 0; i < window_m_; ++i) {
			x_offset -= 1.0;
			weight_x[i] = window_func_(x_offset) * sinc(x_offset);
		}
	}

	if (yd == 0.0) {  // lies on grid lattice
		for (int i = 0; i < window_m_; ++i) {
			weight_y[i] = static_cast<int>(i) == radius_ - 1 ? 1 : 0;
		}
	} else {
		for (int i = 0; i < window_m_; ++i) {
			y_offset -= 1.0;
			weight_y[i] = window_func_(y_offset) * sinc(y_offset);
		}
	}

	if (zd == 0.0) {  // lies on grid lattice
		for (int i = 0; i < window_m_; ++i) {
			weight_z[i] = static_cast<int>(i) == radius_ - 1 ? 1 : 0;
		}
	} else {
		for (int i = 0; i < window_m_; ++i) {
			z_offset -= 1.0;
			weight_z[i] = window_func_(z_offset) * sinc(z_offset);
		}
	}

	// convolve
	double total = 0.0;
	for (int i = -(radius_ - 1); i <= radius_; ++i) {
		int ii = xi + i;             // vol index pos
		int iw = i + (radius_ - 1);  // weight index pos

		// boundary checks
		if ((ii < 0) || (ii >= mat.width))
			continue;

		for (int j = -(radius_ - 1); j <= radius_; ++j) {
			int jj = yi + j;             // vol index pos
			int jw = j + (radius_ - 1);  // weight index pos

			// boundary checks
			if ((jj < 0) || (jj >= mat.height))
				continue;

			for (int k = -(radius_ - 1); k <= radius_; ++k) {
				int kk = zi + k;             // vol index pos
				int kw = k + (radius_ - 1);  // weight index pos

				// boundary checks
				if ((kk < 0) || (kk >= mat.depth))
					continue;

				// multiply weights by value
				double weight = weight_x[iw] * weight_y[jw] * weight_z[kw];
				double value = mat(ii, jj, kk);

				total += (weight * value);
			}
		}
	}

	// cap the intensities
	total = (total < 0) ? 0 : total;
	total = (total > 1) ? 1 : total;

	return total;
}
