#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

#include "Array.h"
#include "fftw++.h"

class Matrix3D {
public:
	Matrix3D(int width = 1, int height = 1, int depth = 1, float fill = 0.0f);
	Matrix3D(std::vector<float> init_vals, int width = 1, int height = 1, int depth = 1);
	Matrix3D(Array::array3<Complex> init_arr);
	Matrix3D(const Matrix3D &other);

	~Matrix3D();

	void deallocate();
	float max();
	float *raw_data();
	std::tuple<int, int, int> size();
	Matrix3D convolve(Matrix3D &m, bool &err);
	Matrix3D convolve(Matrix3D &m, bool wrap, bool &err);
	Matrix3D cap(float cap);
	Matrix3D unequal_neighbourhood(int x, int y, int z, int min_radius, int max_radius);
	Matrix3D neighbourhood(int x, int y, int z, int radius);
	Array::array3<Complex> to_complex_array();

	float &operator()(int x, int y, int z);
	float operator()(int x, int y, int z) const;
	Matrix3D operator*(float scalar);
	Matrix3D operator/(float scalar);
	Matrix3D &operator*=(float scalar);
	Matrix3D &operator/=(float scalar);
	Matrix3D &operator=(Matrix3D other);

	friend void swap(Matrix3D &first, Matrix3D &second);
	friend std::ostream &operator<<(std::ostream &strm, Matrix3D &mat);

	int width, height, depth;

private:
	float *values_;
};

#endif
