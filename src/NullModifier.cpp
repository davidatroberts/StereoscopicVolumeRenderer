#include "NullModifier.hpp"

NullModifier::~NullModifier() {
}

void NullModifier::modify(Matrix3D &mat,Vector &ray_direction, 
	Vector &ray_position, Vector4 &src_rgba) {
	return;
}