#include "CCPrefilteredBSpline.hpp"

#define Pole (sqrt(3.0f)-2.0f)

CCPrefilteredBSpline::CCPrefilteredBSpline(Vector min, Vector max): 
CCInterpolator(min, max) {
	weight_coefficients_[0] = Vector4(-1.0f/6.0f, 0.5f, -0.5f, 1.0f/6.0f);
	weight_coefficients_[1] = Vector4(0.5f, -1.0f, 0.0f, 2.0f/3.0f);
	weight_coefficients_[2] = Vector4(-0.5f, 0.5f, 0.5f, 1.0/6.0f);
	weight_coefficients_[3] = Vector4(1.0f/6.0f, 0.0f, 0.0f, 0.0f);
}

CCPrefilteredBSpline::CCPrefilteredBSpline(const CCPrefilteredBSpline &other)
: CCInterpolator(other.min_, other.max_), 
coeffs_(new float[other.width_*other.height_*other.depth_]) {
	std::copy(other.coeffs_, 
		other.coeffs_ + (other.width_*other.height_*other.depth_), coeffs_);
}

CCPrefilteredBSpline::~CCPrefilteredBSpline() {
	delete[] coeffs_;
}

void CCPrefilteredBSpline::preprocess(Matrix3D &grid) {
	coeffs_ = new float[width_*height_*depth_];
	std::copy(grid.raw_data(), grid.raw_data()+(width_*height_*depth_), 
		coeffs_);

	// determine the coefficients
	samples_to_coefficients(coeffs_);
}

double CCPrefilteredBSpline::interpolate(Vector &position, Matrix3D &mat) {
	double u = position.x - floor(position.x);
	double v = position.y - floor(position.y);
	double w = position.z - floor(position.z);

	Vector4 u_vec(u*u*u, u*u, u, 1);
	Vector4 v_vec(v*v*v, v*v, v, 1);
	Vector4 w_vec(w*w*w, w*w, w, 1);

	// define the weights
	double weights_u_[4];
	double weights_v_[4];
	double weights_w_[4]; 

	// calculate the weights for each dimension
	for (int i=0; i<4; ++i) {
		weights_u_[i] = weight_coefficients_[i].dot(u_vec);
		weights_v_[i] = weight_coefficients_[i].dot(v_vec);
		weights_w_[i] = weight_coefficients_[i].dot(w_vec);
	}

	// do the convolution
	double total = 0.0;
	const int m = 2;
	for (int i=-m+1; i<=m; ++i) {
		int ii = floor(position.x) + i;
		if (ii < 0)
			ii = 0;
		else if (ii >= width_)
			ii = width_-1;

		for (int j=-m+1; j<=m; ++j) {
			int jj = floor(position.y) + j;
			if (jj < 0)
				jj = 0;
			else if (jj >= height_)
				jj= height_-1;

			for (int k=-m+1; k<=m; ++k) {
				int kk = floor(position.z) + k;
				if (kk < 0)
					kk = 0;
				else if (kk >= depth_)
					kk = depth_-1;

				double weight = weights_u_[i+1] * weights_v_[j+1] * 
					weights_w_[k+1];
				float val = coeffs_[(ii + width_ * (jj + height_ * kk))];

				total += (weight * val);
			}
		}
	}

	if (total < 0)
		total = 0;
	if (total > 1)
		total = 1;

	return total;
}

void CCPrefilteredBSpline::samples_to_coefficients(float *volume) {
	unsigned int pitch = width_*sizeof(float);
	samples_to_coefficientsX(volume, pitch, width_, height_, depth_);
	samples_to_coefficientsY(volume, pitch, width_, height_, depth_);
	samples_to_coefficientsZ(volume, pitch, width_, height_, depth_);
}

void CCPrefilteredBSpline::samples_to_coefficientsX(float *volume, 
	unsigned int pitch, unsigned int width, unsigned int height, 
	unsigned int depth) {
	for (int z=0; z<depth_; ++z) {
		for (int y=0; y<height_; ++y) {
			int index = (y*width_) + (z*width_*height_);
			float *c = volume;
			c = c + index;

			convert_to_coefficients(c, width, sizeof(float));
		}
	}
}

void CCPrefilteredBSpline::samples_to_coefficientsY(float *volume, 
	unsigned int pitch, unsigned int width, unsigned int height, 
	unsigned int depth) {
	for (int z=0; z<depth_; ++z) {
		for (int x=0; x<width_; ++x) {
			int index = x + (z * width_ * height_);
			float *c = volume;
			c += index;

			convert_to_coefficients(c, height, pitch);
		}
	}
}

void CCPrefilteredBSpline::samples_to_coefficientsZ(float *volume, 
	unsigned int pitch, unsigned int width, unsigned int height, 
	unsigned int depth) {
	const unsigned int slice = height * pitch;
	for (int y=0; y<height_; ++y) {
		for (int x=0; x<width_; ++x) {
			int index = x + (y * width_);
			float *c = volume;
			c += index;

			convert_to_coefficients(c, depth, slice);
		}
	}
}

void CCPrefilteredBSpline::convert_to_coefficients(float *coeffs, 
	int data_length, int step) {
	const float lambda = (1.0f - Pole) * (1.0f - 1.0f/Pole);

	// causal initialization
	float *c = coeffs;
	float previous_c;
	*c = previous_c = lambda * initial_causal_coefficient(c, data_length, 
		step);

	// causal recursion
	for (int n=1; n < data_length; n++) {
		c = (float*)((unsigned char*)c + step); 
		*c = previous_c = lambda * *c + Pole * previous_c;
	}

	// anticausal initialization
	*c = previous_c = initial_anticausal_coefficient(c, data_length, step);

	// anti-causal recursion
	for (int n = data_length-2; 0 <= n; --n) {
		c = (float*)((unsigned char*)c - step); 
		*c = previous_c = Pole * (previous_c - *c);
	}
}

float CCPrefilteredBSpline::initial_causal_coefficient(float *coeffs, 
	int data_length, int step) {
	int horizon = data_length;

	// we're going to use clamping boundaries as with Thévenaz	
	float zn = Pole;
	float sum = *coeffs;
	for (int n=0; n < horizon; ++n) {
		sum += zn * *coeffs;
		zn *= Pole;
		coeffs = (float*)((unsigned char*)coeffs + step);	
	}

	return sum;
}

float CCPrefilteredBSpline::initial_anticausal_coefficient(float *coeffs, 
	int data_length, int step) {
	// init is using clamping boundaries
	return ((Pole / (Pole - 1.0f)) * *coeffs);
}

void swap(CCPrefilteredBSpline &first, CCPrefilteredBSpline &second) {
	using std::swap;
	swap(first.min_, second.min_);
	swap(first.max_, second.max_);
	swap(first.width_, second.width_);
	swap(first.height_, second.height_);
	swap(first.depth_, second.depth_);
	swap(first.coeffs_, second.coeffs_);
}