#ifndef NULL_MODIFIER
#define NULL_MODIFIER

#include "PointModifier.hpp"

class NullModifier: public PointModifier {
public:
	~NullModifier();

	void modify(Matrix3D &mat, Vector &ray_direction, Vector &ray_position, 
		Vector4 &src_rgba);
};

#endif