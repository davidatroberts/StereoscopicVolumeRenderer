#include "matrix3.hpp"

Matrix3::Matrix3(float fill) {
	std::fill(std::begin(values_), std::end(values_), fill);
}

Matrix3::Matrix3(const Matrix3 &other) : values_(other.values_) {}

void Matrix3::set(int x, int y, float value) {
	values_[int(x + 3 * y)] = value;
}

void Matrix3::set_row_col(int row, int col, float value) {
	values_[int(row + 3 * col)] = value;
}

float Matrix3::get(int x, int y) const {
	return values_[int(x + 3 * y)];
}

float Matrix3::get_row_col(int row, int col) {
	return values_[int(row + 3 * col)];
}

float *Matrix3::raw_data() {
	return values_.data();
}

Matrix3 Matrix3::x_matrix(float angle_rad) {
	return Matrix3{{1.0, 0.0, 0.0, 0.0, cos(angle_rad), -sin(angle_rad), 0.0, sin(angle_rad), cos(angle_rad)}};
}

Matrix3 Matrix3::y_matrix(float angle_rad) {
	return Matrix3{{cos(angle_rad), 0.0, sin(angle_rad), 0.0, 1.0, 0.0, -sin(angle_rad), 0.0, cos(angle_rad)}};
}

Matrix3 Matrix3::z_matrix(float angle_rad) {
	return Matrix3{{cos(angle_rad), -sin(angle_rad), 0.0, sin(angle_rad), cos(angle_rad), 0.0, 0.0, 0.0, 1.0}};
}

Matrix3 Matrix3::scale_matrix(float x_scale, float y_scale, float z_scale) {
	return Matrix3{{x_scale, 0.0, 0.0, 0.0, y_scale, 0.0, 0.0, 0.0, z_scale}};
}

Matrix3 Matrix3::operator*(const Matrix3 &m) const {
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
