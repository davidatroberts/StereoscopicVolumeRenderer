#include "highlight_modifier_decorator.hpp"

#include "util.hpp"

HighlightModifierDecorator::HighlightModifierDecorator(
	CameraModifier *basic_modifier, picojson::value::object &settings_obj,
	ViewSettings view_settings)
	: basic_modifier_(basic_modifier), view_settings_(view_settings) {
	// get the settings
	sphere_radius_ = settings_obj["sphere_radius"].get<double>();
	highlight_colour_.red = settings_obj["red"].get<double>();
	highlight_colour_.green = settings_obj["green"].get<double>();
	highlight_colour_.blue = settings_obj["blue"].get<double>();

	// get the link files
	std::string link_file = settings_obj["link_file"].to_str();
	std::string no_link_file = settings_obj["no_link_file"].to_str();

	// parse the files into lists
	std::vector<Pair> pair_list;
	parse_node_list(link_file, no_link_file, pair_list);

	// get the positions for the pixels for the spheres
	std::vector<Pair> mod_pair_list;
	for (auto p: pair_list) {

		mod_pair_list.push_back(p);
	}
}

HighlightModifierDecorator::HighlightModifierDecorator(
	const HighlightModifierDecorator &other)
	: basic_modifier_(other.basic_modifier_), 
	view_settings_(other.view_settings_),
	sphere_radius_(other.sphere_radius_), 
	highlight_colour_(other.highlight_colour_) {

}

HighlightModifierDecorator::~HighlightModifierDecorator() {
	delete basic_modifier_;
}

void HighlightModifierDecorator::modify(FrameBuffer &buffer) {
	return;
}

void swap(HighlightModifierDecorator &first, 
	HighlightModifierDecorator &second) {
	using std::swap;
	swap(first.basic_modifier_, second.basic_modifier_);
	swap(first.view_settings_, second.view_settings_);
	swap(first.sphere_radius_, second.sphere_radius_);
	swap(first.highlight_colour_, second.highlight_colour_);
}

HighlightModifierDecorator& HighlightModifierDecorator::operator= (
	HighlightModifierDecorator other) {
	swap(*this, other);
	return *this;
}

void HighlightModifierDecorator::parse_node_list(std::string link_file,
	std::string no_link_file, std::vector<Pair> &pair_list) {
	// read the (no)link contents
	bool parsed;
	std::string link_contents = Util::read_file(link_file.c_str(), parsed);
	Util::assert_eq(parsed, "Failed to read LINK json contents");
	std::string no_link_contents = Util::read_file(no_link_file.c_str(), 
		parsed);
	Util::assert_eq(parsed, "Failed to read NO LINK json contents");

	// parse the json content
	picojson::array link_arr, no_link_arr;
	Util::assert_eq(Util::parse_json_array(link_contents, link_arr),
		"Unable to parse LINK array");
	Util::assert_eq(Util::parse_json_array(no_link_contents, no_link_arr),
		"Unable to parse NO LINK array");

	// loop through the arrays and pull into vectors
	for (unsigned int i=0; i<link_arr.size(); ++i) {
		picojson::value link_val = link_arr[i];
		picojson::value no_link_val = no_link_arr[i];

		picojson::array link_pair, no_link_pair;
		Util::assert_eq(Util::parse_json_array(link_val, link_pair),
			"Unable to parse pair");
		Util::assert_eq(Util::parse_json_array(no_link_val, no_link_pair),
			"Unable to parse no link pair");

		// link pairs
		picojson::object pos1, pos2;
		Util::assert_eq(Util::parse_json_obj(link_pair[0], pos1),
			"Unable to parse pos1");
		Util::assert_eq(Util::parse_json_obj(link_pair[1], pos2),
			"Unable to parse pos2");

		// no link pairs
		picojson::object pos3, pos4;
		Util::assert_eq(Util::parse_json_obj(no_link_pair[0], pos3),
			"Unable to parse pos3");
		Util::assert_eq(Util::parse_json_obj(no_link_pair[1], pos4),
			"Unable to parse pos4");

		// read through link values
		Vector n1pos1(
			pos1["x"].get<double>(), 
			pos1["y"].get<double>(),
			pos1["z"].get<double>());
		Vector n1pos2(
			pos2["x"].get<double>(),
			pos2["y"].get<double>(),
			pos2["z"].get<double>());
		Pair p1(Sphere(n1pos1, sphere_radius_), 
				Sphere(n1pos2, sphere_radius_), true);

		// read through nolink values
		Vector n2pos1(
			pos3["x"].get<double>(),
			pos3["y"].get<double>(),
			pos3["z"].get<double>());
		Vector n2pos2(
			pos4["x"].get<double>(),
			pos4["y"].get<double>(),
			pos4["z"].get<double>());
		Pair p2(Sphere(n2pos1, sphere_radius_), 
				Sphere(n2pos2, sphere_radius_), false);

		pair_list.push_back(p1);
		pair_list.push_back(p2);
	}
}

void HighlightModifierDecorator::determine_highlight_positions(
	double x_offset, Pair &p) {

}