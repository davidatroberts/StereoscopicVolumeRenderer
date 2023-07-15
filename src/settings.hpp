#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <vector>
#include <map>
#include <picojson.h>

#include "util.hpp"
#include "vector.hpp"
#include "pair.hpp"

#define VERBOSE
#define BASE_WIDTH 300.0
#define BASE_HEIGHT 300.0

enum class LatticeType {
	CC,
	BCC,
	FCC,
	UNKNOWN
};

enum class InterpolationType {
	CC_TRILINEAR,
	CC_CATMULL,
	CC_INTBSPLINE,
	CC_BSPLINE,
	CC_PRETRILINEAR,
	CC_WINDOWSINC,
	BCC_TRILINEAR,
	FCC_TRILINEAR,
	INCORRECT_TYPE,
	UNKNOWN
};

enum class WindowType {
	RECTANGLE,
	BARTLETT,
	BLACKMAN,
	COSINE_BELL,
	COSINE_WINDOW,
	HAMMING,
	HANN,
	LANCZOS,
	WELCH,
	KAISER,
	UNKNOWN
};

enum class CameraType {
	MONO,
	STEREO,
	ANAGLYPH,
	COLOUR_ANAGLYPH,
	HALFCOLOUR_ANAGLYPH,
	OPTIMISED_ANAGLYPH,
	DUBOIS_ANAGLYPH,
	CROSS_EYE,
	UNKNOWN
};

enum class IlluminationModelType {
	BLINN_PHONG,
	UNKNOWN
};

enum class GradientType {
	CENTRAL_DIFFERENCE,
	UNKNOWN
};

struct ViewSettings {
	CameraType camera;
	bool thread;
	int image_width;
	int image_height;
	int display_width_px;
	float display_width_mm;
	float distance_to_display_mm;
	float IOD_mm;
	float camera_angle;
	Vector camera_axis;
	Colour background_colour;

	// computed from above
	float world_width;
	float image_width_mm;
	float mm_to_world_ratio;
	float IOD_world;
	float distance_to_display_world;

	std::string camera_str;
};

struct RaySettings {
	bool sub_sample;
	bool test_ray;
	double sample_step;
	double subsample_rate;
};

struct VolumeSettings {
	std::string volume_file;
	Vector resolution;
	Vector ratio;
	InterpolationType interpolation;
	WindowType window;
	int window_radius;
	std::map<std::string, double> interpolation_settings;
	LatticeType lattice;
	std::string interpolation_str;
	std::string window_str;
	std::string lattice_str;
};

struct GraphSettings {
	bool highlight_nodes;
	double sphere_radius;
	Colour highlight_colour;
	std::string link_file;
	std::string no_link_file;
	std::vector<Pair> pair_list;
};

struct TransferSettings {
	std::string red_file, green_file, blue_file, alpha_file;
};

struct PointModifierSettings {
	picojson::array parameters;
};

struct CameraModifierSettings {
	picojson::array parameters;
};

struct ShaderSettings {
	IlluminationModelType illumination_model;
	GradientType gradient;
	Vector light_position;
	Vector ka, kd, ks;
	double n;
	Vector light_colour, ambient_colour;
	std::string illumination_str;
	std::string gradient_str;
};

namespace Settings {
	ViewSettings read_view_settings(picojson::value::object &json_obj);
	RaySettings read_ray_settings(picojson::value::object &json_obj);
	VolumeSettings read_volume_settings(picojson::value::object &json_obj);
	GraphSettings read_graph_settings(picojson::value::object &json_obj);
	TransferSettings read_transfer_settings(picojson::value::object &json_obj);
	PointModifierSettings read_point_modifier_settings(
		picojson::value::object &json_obj);
	CameraModifierSettings read_camera_modifier_settings(
		picojson::value::object &json_obj);
	ShaderSettings read_shader_settings(picojson::value::object &json_obj);

	Vector read_vector(picojson::value &json_val);
	Colour read_colour(picojson::value &json_val);

	void parse_node_list(GraphSettings &graph);

	void print(ViewSettings &settings);
	void print(RaySettings &settings);
	void print(VolumeSettings &settings);
	void print(GraphSettings &settings);
	void print(TransferSettings &settings);
	void print(PointModifierSettings &settings);
	void print(ShaderSettings &settings);
}

#endif