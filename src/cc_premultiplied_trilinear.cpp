#include "cc_premultiplied_trilinear.hpp"

#include <math.h>

#include <tuple>

#include "Array.h"
#include "settings.hpp"
// #include "fftw++.h"

CCPremultipliedTrilinear::CCPremultipliedTrilinear(Vector min, Vector max)
	: CCInterpolator(min, max), min_r_range_(1.0), max_r3_range_(15.0217), max_r_range_(2.4674) {}

CCPremultipliedTrilinear::CCPremultipliedTrilinear(const CCPremultipliedTrilinear &other)
	: CCInterpolator(other.min_, other.max_),
	  min_r_range_(other.min_r_range_),
	  max_r3_range_(other.max_r3_range_),
	  max_r_range_(other.max_r_range_) {}

CCPremultipliedTrilinear::~CCPremultipliedTrilinear() {}

void CCPremultipliedTrilinear::preprocess(Matrix3D &grid) {
	#if false
	// convert into complex array
	Array::array3<Complex> spatial = grid.to_complex_array();
	size_t align = sizeof(Complex);
	Array::array3<Complex> freq(spatial.Nx(), spatial.Ny(), spatial.Nz(), align);

	// convert into the frequency domain
	fftwpp::fft3d forward(spatial.Nx(), spatial.Ny(), spatial.Nz(), -1, spatial, freq);
	forward.fft(spatial, freq);
	spatial.Deallocate();

	// copy shift into matrix for convolution later
	Matrix3D vol_m(freq);
	freq.Deallocate();

	// allocate matrix for the prefilter
	Matrix3D prefilter_m(KERNEL_SIZE, KERNEL_SIZE, KERNEL_SIZE);

	// initiate steps for the prefilter in w
	double w_step = (2.0f * M_PI) / ((double)KERNEL_SIZE - 1);
	double ww_step = (2.0f * M_PI) / ((double)KERNEL_SIZE - 1);
	double www_step = (2.0f * M_PI) / ((double)KERNEL_SIZE - 1);

	// generate the prefilter matrix
	double www = -M_PI;
	for (int z = 0; z < KERNEL_SIZE; ++z) {
		double ww = -M_PI;
		for (int y = 0; y < KERNEL_SIZE; ++y) {
			double w = -M_PI;
			for (int x = 0; x < KERNEL_SIZE; ++x) {
				double rx = reciprocal_sin2(w);
				double ry = reciprocal_sin2(ww);
				double rz = reciprocal_sin2(www);

				double r = rx * ry * rz;

				prefilter_m(x, y, z) = r;
				w += w_step;
			}
			ww += ww_step;
		}
		www += www_step;
	}

	float pre_max = prefilter_m.max();
	prefilter_m /= pre_max;

	// convolve the prefilter with the volume
	bool err;
	Matrix3D conv_m = vol_m.convolve(prefilter_m, false, err);
	Util::assert_eq(!err, "Error convolving matrices for premultiplied filter");

	// convert convolved back to array
	Array::array3<Complex> conv = conv_m.to_complex_array();

	// convert back into the spatial domain
	Array::array3<Complex> result(conv.Nx(), conv.Ny(), conv.Nz(), align);
	fftwpp::fft3d backward(conv.Nx(), conv.Ny(), conv.Nz(), 1, conv, result);
	backward.fftNormalized(conv, result);
	conv.Deallocate();

	// put the decimal point in the right place
	Matrix3D result_m(result);
	result_m *= 10;

	// cap any values from being above 1
	result_m = result_m.cap(1.0f);

	// load back into the matrix
	grid = result_m;

	#endif
}

double CCPremultipliedTrilinear::interpolate(const Vector &position, const Matrix3D &mat) const {
	int i = (unsigned int)position.x;
	int j = (unsigned int)position.y;
	int k = (unsigned int)position.z;

	float bx = position.x - i;
	float by = position.y - j;
	float bz = position.z - k;

	return (
		mat(i, j, k) * (1.0f - bx) * (1.0f - by) * (1.0f - bz) + mat(i + 1, j, k) * bx * (1.0f - by) * (1.0f - bz) +
		mat(i + 1, j + 1, k) * bx * by * (1.0f - bz) + mat(i, j + 1, k) * (1.0f - bx) * by * (1.0f - bz) +
		mat(i, j, k + 1) * (1.0f - bx) * (1.0f - by) * bz + mat(i + 1, j, k + 1) * bx * (1.0f - by) * bz +
		mat(i + 1, j + 1, k + 1) * bx * by * bz + mat(i, j + 1, k + 1) * (1.0f - bx) * by * bz);
}

double CCPremultipliedTrilinear::reciprocal_sin2(double w) {
	if (w == 0.0f) {
		return 1;
	}

	double v = (1.0f / pow(((sin(M_PI * w)) / (M_PI * w)), 2.0f)) * pi_w(w);
	return v;
}

double CCPremultipliedTrilinear::pi_w(double w) {
	if ((w >= -M_PI) || (w < M_PI)) {
		return 1;
	}

	return 0;
}

void swap(CCPremultipliedTrilinear &first, CCPremultipliedTrilinear &second) {
	using std::swap;
	swap(first.min_, second.min_);
	swap(first.max_, second.max_);
	swap(first.width_, second.width_);
	swap(first.height_, second.height_);
	swap(first.depth_, second.depth_);
	swap(first.min_r_range_, second.min_r_range_);
	swap(first.max_r3_range_, second.max_r3_range_);
	swap(first.max_r_range_, second.max_r_range_);
}
