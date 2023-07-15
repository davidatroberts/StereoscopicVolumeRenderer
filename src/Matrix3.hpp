#ifndef MATRIX3_H
#define MATRIX3_H

#include <array>
#include <cmath>

class Matrix3 {
public:
	Matrix3(float fill = 0.0f);
	explicit Matrix3(std::array<float, 9> vals) : values_(vals) {}
	Matrix3(const Matrix3 &other);

	void set(int x, int y, float value);
	void set_row_col(int row, int col, float value);
	float get(int x, int y) const;
	float get_row_col(int row, int col);
	float *raw_data();

	static Matrix3 x_matrix(float angle_rad);
	static Matrix3 y_matrix(float angle_rad);
	static Matrix3 z_matrix(float angle_rad);
	static Matrix3 scale_matrix(float x_scale, float y_scale, float z_scale);

	Matrix3 operator*(const Matrix3 &m) const;

private:
	std::array<float, 9> values_;
};

#endif
