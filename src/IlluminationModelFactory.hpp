#ifndef ILLUMINATIONMODEL_FACTORY
#define ILLUMINATIONMODEL_FACTORY

#include <functional>
#include "Settings.hpp"
#include "Vector.hpp"

class IlluminationModelFactory {
public:
	static std::function<Vector(Vector, Vector, Vector, Vector, Vector, 
		Vector, double, Vector, Vector)> make_model(
		IlluminationModelType model_type);
};

#endif