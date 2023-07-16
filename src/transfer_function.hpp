#pragma once

#include <climits>

#include "util.hpp"
#include "vector.hpp"
#include "vector4.hpp"

class TransferFunction {
public:
	TransferFunction(double base_sample_step);
	~TransferFunction();

	void adapt_with_sampling(double sample_step, double base_sample_step);
	void adapt_with_sampling(double sample_step);
	bool map_transfer_function(std::string red, std::string green, std::string blue, std::string alpha);

	// interpolate the transfer function
	inline Vector4 sample_rgba_d(double density) {
		double mapped_density = Util::map_range(min_dens, max_dens, min_trans, max_trans, density);

		double g, gg;
		double target = modf(mapped_density, &g);

		gg = g;

		if (gg < USHRT_MAX)
			gg++;

		Vector4 v1 = transfer_[(unsigned int)g];
		Vector4 v2 = transfer_[(unsigned int)gg];

		Vector4 result;
		result.x = linear(target, v1.x, v2.x);
		result.y = linear(target, v1.y, v2.y);
		result.z = linear(target, v1.z, v2.z);
		result.w = linear(target, v1.w, v2.w);

		return result;
	}

	// inline
	Vector4 sample_rgba_with_sample_step(int density, double sample_step) {
		Vector4 col = transfer_[density];

		col.w = 1.0 - pow(1.0 - col.w, sample_step / base_sample_step_);
		return col;
	}

	inline double linear(double target, double v1, double v2) {
		return (target * (double)v2) + ((1.0f - target) * (double)v1);
	}

private:
	Vector4 transfer_[USHRT_MAX + 1];
	double base_sample_step_;
	double min_dens, max_dens, min_trans, max_trans;
};
