#pragma once

#include <functional>
#include <map>

#include "settings.hpp"

class WindowFactory {
public:
	WindowFactory();

	std::function<double(double)> make_window(
		WindowType window_type, int radius,
		std::map<std::string, double> interpolation_settings = std::map<std::string, double>{});
};
