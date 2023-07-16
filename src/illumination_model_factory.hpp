#pragma once

#include <functional>
#include "settings.hpp"
#include "vector.hpp"

class IlluminationModelFactory {
public:
	static std::function<Vector(Vector, Vector, Vector, Vector, Vector, 
		Vector, double, Vector, Vector)> make_model(
		IlluminationModelType model_type);
};
