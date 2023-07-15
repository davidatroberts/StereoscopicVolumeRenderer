#include "matrix_3d.hpp"

Matrix3D::Matrix3D(int width, int height, int depth, float fill) : width(width), height(height), depth(depth) {
	if ((width > 0) && (height > 0) && (depth > 0)) {
		values_ = new float[width * height * depth];
		std::fill(values_, values_ + (width * height * depth), fill);
	} else {
		values_ = NULL;
	}
}

Matrix3D::Matrix3D(std::vector<float> init_vals, int width, int height, int depth)
	: width(width), height(height), depth(depth) {
	if ((width > 0) && (height > 0) && (depth > 0)) {
		values_ = new float[width * height * depth];
		std::fill(values_, values_ + (width * height * depth), 0.0);

		// copy values from vector ONLY if it is the size of the matrix
		if (init_vals.size() == (width * height * depth)) {
			std::copy(init_vals.begin(), init_vals.end(), values_);
		}
	} else {
		values_ = NULL;
	}
}

Matrix3D::Matrix3D(Array::array3<std::complex<float>> init_arr)
	: width(init_arr.Nx()), height(init_arr.Ny()), depth(init_arr.Nz()) {
	values_ = new float[init_arr.Nx() * init_arr.Ny() * init_arr.Nz()];
	for (int z = 0; z < depth; ++z) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				std::complex<float> cmp = init_arr(x, y, z);
				float val = std::abs(cmp);
				(*this)(x, y, z) = val;
			}
		}
	}
}

Matrix3D::Matrix3D(const Matrix3D &other)
	: width(other.width),
	  height(other.height),
	  depth(other.depth),
	  values_(new float[other.width * other.height * other.depth]) {
	std::copy(other.values_, other.values_ + (other.width * other.height * other.depth), values_);
}

Matrix3D::~Matrix3D() {
	delete[] values_;
}

void Matrix3D::deallocate() {
	delete[] values_;
}

float Matrix3D::max() {
	float max = 0;
	for (int i = 0; i < (width * height * depth); ++i) {
		max += values_[i];
	}

	return max;
}

float *Matrix3D::raw_data() {
	return values_;
}

std::tuple<int, int, int> Matrix3D::size() {
	return std::make_tuple(width, height, depth);
}

Matrix3D Matrix3D::convolve(Matrix3D &m, bool &err) {
	return convolve(m, true, err);
}

Matrix3D Matrix3D::convolve(Matrix3D &m, bool wrap, bool &err) {
	err = false;

	Matrix3D result(width, height, depth);

	// error if filter isn't equal size
	if (!(m.width == m.height && m.width == m.depth)) {
		err = true;
		return result;
	}

	// error if not odd size
	if (m.width % 2 == 0) {
		err = true;
		return result;
	}

	// get the middle position of the matrix
	int midx = m.width / 2;
	int midy = m.height / 2;
	int midz = m.depth / 2;

	// iterate through the matrix and convolve with the mask m
	for (int z = 0; z < depth; z++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				double value = 0.0;

				for (int mz = 0; mz < m.depth; mz++) {
					for (int my = 0; my < m.height; my++) {
						for (int mx = 0; mx < m.width; mx++) {
							// get positions to index the matrix
							int x_index = x + (mx - midx);
							int y_index = y + (my - midy);
							int z_index = z + (mz - midz);

							// check if indices of cc out of range
							bool out_of_range = false;
							if (x_index < 0) {
								x_index = width + x_index;
								out_of_range = true;
							} else if (x_index >= width) {
								x_index = x_index - width;
								out_of_range = true;
							}

							if (y_index < 0) {
								y_index = height + y_index;
								out_of_range = true;
							} else if (y_index >= height) {
								y_index = y_index - height;
								out_of_range = true;
							}

							if (z_index < 0) {
								z_index = depth + z_index;
								out_of_range = true;
							} else if (z_index >= depth) {
								z_index = z_index - depth;
								out_of_range = true;
							}

							if (out_of_range && (wrap == false)) {
								continue;
							}

							double mask_value = m(mx, my, mz);
							double cc_value = (*this)(x_index, y_index, z_index);

							value += cc_value * mask_value;
						}
					}
				}
				result(x, y, z) = value;
			}
		}
	}

	return result;
}

Matrix3D Matrix3D::cap(float cap) {
	Matrix3D mat(*this);
	for (int z = 0; z < depth; ++z) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (mat(x, y, z) > cap) {
					mat(x, y, z) = cap;
				}
			}
		}
	}

	return mat;
}

Matrix3D Matrix3D::unequal_neighbourhood(int x, int y, int z, int min_radius, int max_radius) {
	int x_is = x - min_radius;
	int y_is = y - min_radius;
	int z_is = z - min_radius;

	// index offsets (end)
	int x_ie = x + max_radius;
	int y_ie = y + max_radius;
	int z_ie = z + max_radius;

	// initial sizes
	int fullsize = (min_radius + max_radius) + 1;
	int xsize = fullsize;
	int ysize = fullsize;
	int zsize = fullsize;

	// determine size of the submatrix
	// takes into account boundaries
	if (x_is < 0)
		xsize = fullsize + x_is;
	if (y_is < 0)
		ysize = fullsize + y_is;
	if (z_is < 0)
		zsize = fullsize + z_is;

	// take into account max boundaries
	if (x_ie >= width)
		xsize = xsize - (x_ie - (width - 1));
	if (y_ie >= height)
		ysize = ysize - (y_ie - (height - 1));
	if (z_ie >= depth)
		zsize = zsize - (z_ie - (depth - 1));

	// create the new submatrix
	Matrix3D sub(xsize, ysize, zsize);

	// adjust the index positions to ensure that the neighbourhood is ok
	x_is = x_is < 0 ? 0 : x_is;
	y_is = y_is < 0 ? 0 : y_is;
	z_is = z_is < 0 ? 0 : z_is;
	x_ie = x_ie >= width ? width - 1 : x_ie;
	y_ie = y_ie >= height ? height - 1 : y_ie;
	z_ie = z_ie >= depth ? depth - 1 : z_ie;

	// loop through and place the values into the sub matrix
	int sk = 0;
	for (int k = z_is; k <= z_ie; ++k) {
		int sj = 0;
		for (int j = y_is; j <= y_ie; ++j) {
			int si = 0;
			for (int i = x_is; i <= x_ie; ++i) {
				sub(si, sj, sk) = (*this)(i, j, k);
				si++;
			}
			sj++;
		}
		sk++;
	}

	return sub;
}

Matrix3D Matrix3D::neighbourhood(int x, int y, int z, int radius) {
	return unequal_neighbourhood(x, y, z, radius, radius);
}

Array::array3<std::complex<float>> Matrix3D::to_complex_array() {
	size_t align = sizeof(std::complex<float>);
	Array::array3<std::complex<float>> arr(width, height, depth, align);

	for (int z = 0; z < depth; ++z) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				float val = (*this)(x, y, z);
				arr(x, y, z) = val;
			}
		}
	}

	return arr;
}

float &Matrix3D::operator()(int x, int y, int z) {
	return values_[int(x + width * (y + height * z))];
}

float Matrix3D::operator()(int x, int y, int z) const {
	return values_[int(x + width * (y + height * z))];
}

Matrix3D Matrix3D::operator*(float scalar) {
	Matrix3D mat(*this);
	for (int z = 0; z < depth; ++z) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				mat(x, y, z) = mat(x, y, z) * scalar;
			}
		}
	}

	return mat;
}

Matrix3D Matrix3D::operator/(float scalar) {
	Matrix3D mat(*this);
	for (int z = 0; z < depth; ++z) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				mat(x, y, z) = mat(x, y, z) / scalar;
			}
		}
	}

	return mat;
}

Matrix3D &Matrix3D::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}

Matrix3D &Matrix3D::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}

Matrix3D &Matrix3D::operator=(Matrix3D other) {
	swap(*this, other);
	return *this;
}

void swap(Matrix3D &first, Matrix3D &second) {
	using std::swap;
	swap(first.width, second.width);
	swap(first.height, second.height);
	swap(first.depth, second.depth);
	swap(first.values_, second.values_);
}

std::ostream &operator<<(std::ostream &strm, Matrix3D &mat) {
	for (int z = 0; z < mat.depth; ++z) {
		for (int y = 0; y < mat.height; ++y) {
			for (int x = 0; x < mat.width; ++x) {
				strm << mat(x, y, z) << ", ";
			}
			strm << std::endl;
		}
		strm << std::endl;
	}

	return strm;
}
