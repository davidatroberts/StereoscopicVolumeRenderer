#ifndef MATRIX3_H
#define MATRIX3_H

#include <cmath>
#include <vector>

class Matrix3 {
public:
	Matrix3(float fill = 0.0f);
	Matrix3(std::vector<float> init_vals);
	Matrix3(const Matrix3 &other);

	~Matrix3();

	void set(int x, int y, float value);
	void set_row_col(int row, int col, float value);
	float get(int x, int y) const;
	float get_row_col(int row, int col);
	float *raw_data();
	static Matrix3 x_matrix(float angle_rad);
	static Matrix3 y_matrix(float angle_rad);
	static Matrix3 z_matrix(float angle_rad);
	static Matrix3 scale_matrix(float x_scale, float y_scale, float z_scale);

	Matrix3 operator*(Matrix3 &m);

	friend void swap(Matrix3 &first, Matrix3 &second);
	Matrix3 &operator=(Matrix3 other);

private:
	int width_, height_;
	float *values_;
};

#endif
