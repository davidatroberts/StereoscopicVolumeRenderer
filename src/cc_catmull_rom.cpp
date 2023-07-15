#include "cc_catmull_rom.hpp"

CCCatmullRom::CCCatmullRom(Vector min, Vector max) : CCInterpolator(min, max) {
	weight_coefficients_[0] = Vector4(-0.5, 1, -0.5, 0);
	weight_coefficients_[1] = Vector4(1.5, -2.5, 0, 1);
	weight_coefficients_[2] = Vector4(-1.5, 2, 0.5, 0);
	weight_coefficients_[3] = Vector4(0.5, -0.5, 0, 0);
}

CCCatmullRom::~CCCatmullRom() {}

void CCCatmullRom::preprocess(Matrix3D &mat) {}

double CCCatmullRom::interpolate(const Vector &position, const Matrix3D &mat) const {
	double u = position.x - floor(position.x);
	double v = position.y - floor(position.y);
	double w = position.z - floor(position.z);

	Vector4 u_vec(u * u * u, u * u, u, 1);
	Vector4 v_vec(v * v * v, v * v, v, 1);
	Vector4 w_vec(w * w * w, w * w, w, 1);

	// define the weights
	double weights_u_[4];
	double weights_v_[4];
	double weights_w_[4];

	// calculate the weights for each dimension
	for (int i = 0; i < 4; ++i) {
		weights_u_[i] = weight_coefficients_[i].dot(u_vec);
		weights_v_[i] = weight_coefficients_[i].dot(v_vec);
		weights_w_[i] = weight_coefficients_[i].dot(w_vec);
	}

	double total = 0.0;
	const int m = 2;
	for (int i = -m + 1; i <= m; ++i) {
		int ii = floor(position.x) + i;
		if (ii < 0)
			ii = 0;
		else if (ii >= width_)
			ii = width_ - 1;

		for (int j = -m + 1; j <= m; ++j) {
			int jj = floor(position.y) + j;
			if (jj < 0)
				jj = 0;
			else if (jj >= height_)
				jj = height_ - 1;

			for (int k = -m + 1; k <= m; ++k) {
				int kk = floor(position.z) + k;
				if (kk < 0)
					kk = 0;
				else if (kk >= depth_)
					kk = depth_ - 1;

				double weight = weights_u_[i + 1] * weights_v_[j + 1] * weights_w_[k + 1];
				float val = mat(ii, jj, kk);

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
