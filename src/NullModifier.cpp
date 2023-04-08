#include "NullModifier.hpp"

NullModifier::~NullModifier() {}

void NullModifier::modify(Matrix3D &mat, const Vector &ray_direction, const Vector &ray_position, Vector4 &src_rgba) {
	return;
}
