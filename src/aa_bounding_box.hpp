#pragma once

#include "vector.hpp"
#include "util.hpp"
#include "lattice.hpp"

class AABoundingBox {
public:
	AABoundingBox(Vector bboxmin, Vector bboxmax, Lattice *lattice);
	~AABoundingBox();

	bool hit(Vector ray_origin, Vector ray_direction, Vector &ray_start, Vector &ray_end);

	double intersect(Vector &ray_position);

	Vector bboxmin;
	Vector bboxmax;
	Lattice *lattice;
};
