#include "cc_premultiplied_trilinear.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math.h>
#include <random>

#include "vector.hpp"
#include "matrix_3d.hpp"

TEST(testCCPremultipliedTrilinear, DISABLED_testPreprocess) {
	// create the interpolation filter
	Vector min(0, 0, 0);
	Vector max(8, 8, 8);
	CCPremultipliedTrilinear pretrilinear(min, max);

	// create the matrix with random numbers
	Matrix3D grid(8, 8, 8, 0.5f);

	// preprocess and output
	pretrilinear.preprocess(grid);
}