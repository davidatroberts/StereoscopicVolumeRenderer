#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "cc_window_sinc.hpp"
#include "matrix_3d.hpp"
#include "vector.hpp"
#include "window_factory.hpp"

TEST(WindowSincTest, DISABLED_testCosineBell) {
	int radius = 4;

	WindowFactory window_factory;
	auto window_func = window_factory.make_window(WindowType::COSINE_BELL, radius);

	ASSERT_TRUE(window_func != NULL);

	double offset = 4.5;
	for (int i = 0; i < 10; ++i) {
		double value = window_func(offset);
		std::cout << "x: " << offset << " val: " << value << std::endl;

		offset -= 1.0f;
	}
}

TEST(WindowSincTest, DISABLED_testSinc) {
	int window_size = 8;
	int radius = 4;

	// make the window
	WindowFactory window_factory;
	auto window_func = window_factory.make_window(WindowType::COSINE_BELL, radius);

	// create the windowsinc interpolator
	CCWindowSinc window_sinc(Vector(0, 0, 0), Vector(64, 64, 64), radius, window_func);

	// loop through and see what the output values are
	double offset = 4.5;
	for (int i = 0; i < window_size; ++i) {
		offset -= 1.0;
		double val = window_sinc.sinc(offset);
		std::cout << val << std::endl;
	}
}

TEST(WindowSincTest, DISABLED_testCosineBellSinc) {
	int window_size = 8;
	int radius = 4;

	// make the window
	WindowFactory window_factory;
	auto window_func = window_factory.make_window(WindowType::COSINE_BELL, radius);

	// create the windowsinc interpolator
	CCWindowSinc window_sinc(Vector(0, 0, 0), Vector(64, 64, 64), radius, window_func);

	// loop through and see what the output combined valuesare
	double offset = 4.5;
	for (int i = 0; i < window_size; ++i) {
		offset -= 1.0;
		double rect_val = window_func(offset);
		double sinc_val = window_sinc.sinc(offset);
		double comb_val = rect_val * sinc_val;
		std::cout << comb_val << std::endl;
	}
}

TEST(WindowSincTest, DISABLED_WindowSincTest) {
	int radius = 4;

	// make the window function
	WindowFactory window_factory;
	auto window_func = window_factory.make_window(WindowType::COSINE_BELL, radius);

	// make the windowsinc interpolator
	CCWindowSinc window_sinc(Vector(0, 0, 0), Vector(64, 64, 64), radius, window_func);

	// create the volume matrix
	Matrix3D mat(64, 64, 64, 1.0f);

	// create the sample point
	Vector pos(32.5, 32.5, 32.5);

	// get the value of the sample point
	double value = window_sinc.interpolate(pos, mat);

	std::cout << "sinc value: " << value << std::endl;
}
