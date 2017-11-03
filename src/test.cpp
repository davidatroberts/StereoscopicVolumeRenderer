#include "gtest/gtest.h"
#include "testCCPremultipliedTrilinear.hpp"
#include "testMatrix3D.hpp"
#include "testWindowSinc.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}