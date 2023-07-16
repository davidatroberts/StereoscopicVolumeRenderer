#include "gradient_factory.hpp"

#include "cc_trilinear.hpp"

std::function<Vector(Matrix3D &mat, Vector)> GradientFactory::make_gradient(
	GradientType gradient_type, Vector res_max) {
	switch (gradient_type) {
		case GradientType::CENTRAL_DIFFERENCE: {
			return [&res_max](Matrix3D &mat, Vector pos) {
				// std::cout << "made it to the function" << std::endl;

				// interpolation function to use
				CCTrilinear tri(Vector(0, 0, 0), res_max);

				// limits of the volume
				Vector min(0, 0, 0);
				Vector max(1, 1, 1);

				// scale to volume range
				pos = pos.map_range(min, max, min, res_max);

				std::cout << "Pre-interpolation" << std::endl;

				// get the six samples needed
				Vector sample_pos = pos;
				Vector s1, s2;
				sample_pos.x = pos.x - 1;
				s1.x = tri.interpolate(sample_pos, mat);
				sample_pos = pos;
				sample_pos.y = pos.y - 1;
				s1.y = tri.interpolate(sample_pos, mat);
				sample_pos = pos;
				sample_pos.z = pos.z - 1;
				s1.z = tri.interpolate(sample_pos, mat);

				sample_pos = pos;
				sample_pos.x = pos.x + 1;
				s2.x = tri.interpolate(sample_pos, mat);
				sample_pos = pos;
				sample_pos.y = pos.y + 1;
				s2.y = tri.interpolate(sample_pos, mat);
				sample_pos = pos;
				sample_pos.z = pos.z + 1;
				s2.z = tri.interpolate(sample_pos, mat);

				std::cout << "Post interpolation" << std::endl;

				// central difference
				Vector n = (s1 - s2).normalized();
				return n;
			};
		}
		default:
			return NULL;
	}
}
