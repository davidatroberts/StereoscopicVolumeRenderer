#include "IlluminationModelFactory.hpp"

#include <cmath>

Vector blinn_phong(Vector normal, Vector view_direction, 
	Vector light_direction, Vector ka, Vector kd, Vector ks, 
	double shininess, Vector light_colour, Vector ambient_colour) {
	// calculate the halfway vector
	Vector half = light_direction + view_direction;
	half = half.normalized();

	// compute ambient term
	Vector ambient = ka * ambient_colour;

	// compute the diffuse term
	double diffuse_light = std::max(light_direction.dot(normal), 0.0);
	Vector diffuse = kd * light_colour * diffuse_light;

	// compute the specular term
	double specular_light = pow(std::max(half.dot(normal), 0.0), 
		shininess);
	if (diffuse_light <= 0)
		specular_light = 0;
	Vector specular = ks * light_colour * specular_light;

	return ambient + diffuse + specular;
}

std::function<Vector(Vector, Vector, Vector, Vector, Vector, 
	Vector, double, Vector, Vector)> IlluminationModelFactory::make_model(
	IlluminationModelType model_type) {
	switch (model_type) {
		case IlluminationModelType::BLINN_PHONG: {
			return blinn_phong;
		}
		default:
			return NULL;
	}
}