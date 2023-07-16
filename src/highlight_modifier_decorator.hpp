#pragma once

#include <vector>
#include <picojson.h>

#include "camera_modifier.hpp"
#include "frame_buffer.hpp"
#include "pair.hpp"
#include "settings.hpp"

class HighlightModifierDecorator: public CameraModifier {
public:
	HighlightModifierDecorator(CameraModifier *basic_modifier,
		picojson::value::object &settings_obj, ViewSettings view_settings);
	HighlightModifierDecorator(const HighlightModifierDecorator &other);

	~HighlightModifierDecorator();

	void modify(FrameBuffer &buffer);

	friend void swap(HighlightModifierDecorator& first,
		HighlightModifierDecorator &second);
	HighlightModifierDecorator& operator= (HighlightModifierDecorator other);

private:
	void parse_node_list(std::string link_file, std::string no_link_file, 
		std::vector<Pair> &pair_list);
	void determine_highlight_positions(double x_offset, Pair &p);

	CameraModifier *basic_modifier_;
	ViewSettings view_settings_;
	double sphere_radius_;
	Colour highlight_colour_;
};
