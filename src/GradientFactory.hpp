#ifndef GRADIENT_FACTORY
#define GRADIENT_FACTORY

#include <functional>
#include "Matrix3D.hpp"
#include "Settings.hpp"
#include "Vector.hpp"

class GradientFactory {
public:
	static std::function<Vector(Matrix3D &mat, Vector)> make_gradient(
		GradientType gradient_type, Vector res_max);

};

#endif