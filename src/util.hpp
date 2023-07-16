#pragma once

#include <picojson.h>
#include <stdint.h>

#include <cmath>
#include <complex>
#include <fstream>
#include <string>

#include "Array.h"

struct Colour {
	double red;
	double green;
	double blue;
	double alpha;

	void operator+=(const struct Colour &c) {
		red += c.red;
		green += c.green;
		blue += c.blue;
		alpha += c.alpha;
	}
};
typedef struct Colour Colour;

namespace Util {
void assert_eq(bool eq, std::string message);
void read_short_file_as_float(std::ifstream &file, float *data, int size);
void circshift3d(
	Array::array3<std::complex<float>> &in, Array::array3<std::complex<float>> &out, int xshift, int yshift,
	int zshift);
void shift3d(Array::array3<std::complex<float>> &in, Array::array3<std::complex<float>> &out);
bool solve_quad(double a, double b, double c, double &t1, double &t2);
inline bool is_positive(float x) {
	return x >= 0;
};
bool near(double a, double b);
bool parse_json_array(std::string content, picojson::array &arr);
bool parse_json_array(picojson::value val, picojson::array &arr);
bool parse_json_obj(picojson::value val, picojson::object &obj);
int round_to_int(double val);
float clamp(float x, float min, float max);
float byte_to_float(unsigned char *buf);
double compute_x_scale(double base_width, int vp_width);
double compute_y_scale(double base_height, int vp_height);
double compute_world_width(int vp_width, int vp_height, double base_width, double base_height);
inline double map_range(double a, double b, double c, double d, double x) {
	return (x - a) / (b - a) * (d - c) + c;
};
std::string read_file(const char *filename, bool &parsed);

extern double epsilon;
}  // namespace Util
