#ifndef POINT_MODIFIER
#define POINT_MODIFIER

#include "Matrix3D.hpp"
#include "Vector.hpp"
#include "Vector4.hpp"

class PointModifier {
public:
	virtual ~PointModifier() {
	}
	
	virtual void modify(Matrix3D &mat, Vector &ray_direction, 
		Vector &ray_position, Vector4 &src_rgba) = 0;
};

#endif