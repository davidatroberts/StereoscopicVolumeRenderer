#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <iostream>
#include "matrix_3d.hpp"

TEST(Matrix3DTest, testConvolve) {
	const int size = 16;
	Matrix3D mat(size, size, size, 0.0f);

	for (int z=0; z<size; z++) {
		for (int y=0; y<size; y++) {
			for (int x=0; x<size; x++) {
				// fill odd with 0
				if ((x%2==1) && (y%2==1) && (z%2==1)) {
					mat(x, y, z) = 1.0f;
				}
				if ((x%2==0) && (y%2==0) && (z%2==0)) {
					mat(x, y, z) = 1.0f;
				}
			}
		}
	}

	std::vector<float> mask_vals = {
		0.0, 0.0, 0.0,			
		0.0, 0.5, 0.0,
		0.0, 0.0, 0.0,

		0.0, 0.5, 0.0,
		0.5, 1.0, 0.5,
		0.0, 0.5, 0.0,

		0.0, 0.0, 0.0,
		0.0, 0.5, 0.0,
		0.0, 0.0, 0.0
	};
	Matrix3D mask(mask_vals, 3, 3, 3);

	bool err;
	mat = mat.convolve(mask, err);

	ASSERT_FALSE(err);

	bool equal = true;
	int count = 0;
	for (int z=0; z<size; z++) {
		for (int y=0; y<size; y++) {
			for (int x=0; x<size; x++) {
				float val = mat(x, y, z);
				if (val != 1.0f) {
					count++;
					equal = false;
				}
			}
		}
	}

	EXPECT_TRUE(equal);
}

TEST(Matrix3DTest, testMax) {
	std::vector<float> vals = {
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	};

	Matrix3D mat(vals, 3, 3, 3);

	float max = mat.max();
	float expected = 27.0;

	ASSERT_EQ(expected, max);
}

TEST(Matrix3DTest, testDivScalar) {
	std::vector<float> vals = {
		1.0, 4.5, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	};
	Matrix3D mat(vals, 3, 3, 3);

	Matrix3D div_mat = mat / 2.0;

	// check the new matrix has the correct values
	ASSERT_EQ(0.5, div_mat(0, 0, 0));
	ASSERT_EQ(2.25, div_mat(1, 0, 0));

	// make sure the original matrix is not touched
	ASSERT_EQ(1.0, mat(0, 0, 0));
}

TEST(Matrix3DTest, testMultScalar) {
	std::vector<float> vals = {
		1.0, 4.5, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	};
	Matrix3D mat(vals, 3, 3, 3);

	Matrix3D mult_mat = mat * 10.0;

	// check the new matrix has the correct values
	ASSERT_EQ(10.0, mult_mat(0, 0, 0));
	ASSERT_EQ(45.0, mult_mat(1, 0, 0));

	// make sure the original matrix is not touched
	ASSERT_EQ(1.0, mat(0, 0, 0));
}

TEST(Matrix3DTest, testDivScalarInPlace) {
	std::vector<float> vals = {
		1.0, 4.5, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	};
	Matrix3D mat(vals, 3, 3, 3);

	mat /= 2.0;

	// check the new matrix has the correct values
	ASSERT_EQ(0.5, mat(0, 0, 0));
	ASSERT_EQ(2.25, mat(1, 0, 0));
}

TEST(Matrix3DTest, testMultScalarInPlace) {
	std::vector<float> vals = {
		1.0, 4.5, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	};
	Matrix3D mat(vals, 3, 3, 3);

	mat *= 10.0;

	// check the original matrix has updated values
	ASSERT_EQ(10.0, mat(0, 0, 0));
	ASSERT_EQ(45.0, mat(1, 0, 0));
}

TEST(Matrix3DTest, testCap) {
	std::vector<float> vals = {
		1.20, 4.5, 0.97,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,

		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	};
	Matrix3D mat(vals, 3, 3, 3);

	Matrix3D capped = mat.cap(1.0f);

	// check that the cap has worked
	ASSERT_EQ(1.0f, capped(0, 0, 0));
	ASSERT_EQ(1.0f, capped(1, 0, 0));
	ASSERT_EQ(0.97f, capped(2, 0, 0));

	// check that the original matrix is untouched
	ASSERT_EQ(1.20f, mat(0, 0, 0));
}

TEST(Matrix3DTest, testNeighbour) {
	Matrix3D mat(9, 9, 9, 1.0f);

	// get sub matrix in the middle 3, 3, 3
	Matrix3D neighbourhood = mat.neighbourhood(4, 4, 4, 3);

	// check the size is correct
	ASSERT_EQ(7, neighbourhood.width);
	ASSERT_EQ(7, neighbourhood.height);
	ASSERT_EQ(7, neighbourhood.depth);

	// get sub matrix that goes outside min of boundary
	neighbourhood = mat.neighbourhood(0, 0, 0, 3);

	// check the size is correct
	ASSERT_EQ(4, neighbourhood.width);
	ASSERT_EQ(4, neighbourhood.height);
	ASSERT_EQ(4, neighbourhood.depth);

	// get sub matrix that goes outside max of boundary
	neighbourhood = mat.neighbourhood(8, 8, 8, 3);

	// check the size is correct
	ASSERT_EQ(4, neighbourhood.width);
	ASSERT_EQ(4, neighbourhood.height);
	ASSERT_EQ(4, neighbourhood.depth);

	// get sub matrix where only width is lower than min
	neighbourhood = mat.neighbourhood(2, 3, 3, 3);

	// check sizes are correct
	ASSERT_EQ(6, neighbourhood.width);
	ASSERT_EQ(7, neighbourhood.height);
	ASSERT_EQ(7, neighbourhood.depth);

	// get sub matrix where only width is greater than max
	neighbourhood = mat.neighbourhood(6, 5, 5, 3);

	// check sizes are correct
	ASSERT_EQ(6, neighbourhood.width);
	ASSERT_EQ(7, neighbourhood.height);
	ASSERT_EQ(7, neighbourhood.depth);
}

TEST(Matrix3DTest, testUnequalNeighbour) {
	Matrix3D mat(9, 9, 9, 1.0f);

	Matrix3D neighbourhood = mat.unequal_neighbourhood(3, 3, 3, 1, 2);
	ASSERT_EQ(4, neighbourhood.width);
	ASSERT_EQ(4, neighbourhood.height);
	ASSERT_EQ(4, neighbourhood.depth); 

	neighbourhood = mat.unequal_neighbourhood(6, 6, 6, 1, 2);
	ASSERT_EQ(4, neighbourhood.width);
	ASSERT_EQ(4, neighbourhood.height);
	ASSERT_EQ(4, neighbourhood.depth);

	neighbourhood = mat.unequal_neighbourhood(0, 1, 1, 1, 2);
	ASSERT_EQ(3, neighbourhood.width);
	ASSERT_EQ(4, neighbourhood.height);
	ASSERT_EQ(4, neighbourhood.depth);

	neighbourhood = mat.unequal_neighbourhood(7, 6, 6, 1, 2);
	ASSERT_EQ(3, neighbourhood.width);
	ASSERT_EQ(4, neighbourhood.height);
	ASSERT_EQ(4, neighbourhood.depth);
}