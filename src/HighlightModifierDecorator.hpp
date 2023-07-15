#ifndef HIGHLIGHT_MODIFIER_DECORATOR
#define HIGHLIGHT_MODIFIER_DECORATOR

#include <vector>
#include <picojson.h>

#include "CameraModifier.hpp"
#include "FrameBuffer.hpp"
#include "Pair.hpp"
#include "Settings.hpp"

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

#endif