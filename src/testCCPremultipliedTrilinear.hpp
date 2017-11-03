#ifndef TEST_CC_PREMULTIPLIED_TRILINEAR
#define TEST_CC_PREMULTIPLIED_TRILINEAR

#include "CCPremultipliedTrilinear.hpp"

#include <math.h>
#include <random>

#include "Vector.hpp"
#include "Matrix3D.hpp"

class testCCPremultipliedTrilinear: public::testing::Test {
protected:
	static void SetupTestCase() {

	}
};

TEST_F(testCCPremultipliedTrilinear, testPreprocess) {
	// create the interpolation filter
	Vector min(0, 0, 0);
	Vector max(8, 8, 8);
	CCPremultipliedTrilinear pretrilinear(min, max);

	// create the matrix with random numbers
	Matrix3D grid(8, 8, 8, 0.5f);

	// preprocess and output
	pretrilinear.preprocess(grid);
}

#endif