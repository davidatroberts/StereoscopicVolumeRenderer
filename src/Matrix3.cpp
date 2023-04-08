#include "Matrix3.hpp"

Matrix3::Matrix3(float fill) : width_(3), height_(3), values_(new float[width_ * height_]) {
	std::fill(values_, values_ + (width_ * height_), fill);
}

Matrix3::Matrix3(std::vector<float> init_vals) : width_(3), height_(3), values_(new float[width_ * height_]) {
	if (init_vals.size() == (width_ * height_)) {
		std::copy(init_vals.begin(), init_vals.end(), values_);
	}
}

Matrix3::Matrix3(const Matrix3 &other)
	: width_(other.width_), height_(other.height_), values_(new float[other.width_ * other.height_]) {
	std::copy(other.values_, other.values_ + (other.width_ * other.height_), values_);
}

Matrix3::~Matrix3() {
	delete[] values_;
}

void Matrix3::set(int x, int y, float value) {
	values_[int(x + width_ * y)] = value;
}

void Matrix3::set_row_col(int row, int col, float value) {
	values_[int(row + width_ * col)] = value;
}

float Matrix3::get(int x, int y) const {
	return values_[int(x + width_ * y)];
}

float Matrix3::get_row_col(int row, int col) {
	return values_[int(row + width_ * col)];
}

float *Matrix3::raw_data() {
	return values_;
}

Matrix3 Matrix3::x_matrix(float angle_rad) {
	const std::vector<float> vals = {1.0,
									 0.0,
									 0.0,
									 0.0,
									 (float)cos(angle_rad),
									 (float)-sin(angle_rad),
									 0.0,
									 (float)sin(angle_rad),
									 (float)cos(angle_rad)};

	return Matrix3(vals);
}

Matrix3 Matrix3::y_matrix(float angle_rad) {
	const std::vector<float> vals = {(float)cos(angle_rad),  0.0, (float)sin(angle_rad), 0.0, 1.0, 0.0,
									 (float)-sin(angle_rad), 0.0, (float)cos(angle_rad)};

	return Matrix3(vals);
}

Matrix3 Matrix3::z_matrix(float angle_rad) {
	const std::vector<float> vals = {(float)cos(angle_rad),
									 (float)-sin(angle_rad),
									 0.0,
									 (float)sin(angle_rad),
									 (float)cos(angle_rad),
									 0.0,
									 0.0,
									 0.0,
									 1.0};

	return Matrix3(vals);
}

Matrix3 Matrix3::scale_matrix(float x_scale, float y_scale, float z_scale) {
	const std::vector<float> vals = {x_scale, 0.0, 0.0, 0.0, y_scale, 0.0, 0.0, 0.0, z_scale};

	return Matrix3(vals);
}

Matrix3 Matrix3::operator*(Matrix3 &m) {
	Matrix3 ab;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float val = 0.0;
			for (int k = 0; k < 3; k++) {
				val += get(i, k) * m.get(k, j);
			}

			ab.set(i, j, val);
		}
	}

	return ab;
}

void swap(Matrix3 &first, Matrix3 &second) {
	using std::swap;
	swap(first.width_, second.width_);
	swap(first.height_, second.height_);
	swap(first.values_, second.values_);
}

Matrix3 &Matrix3::operator=(Matrix3 other) {
	swap(*this, other);
	return *this;
}
