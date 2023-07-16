#pragma once

#include "aa_bounding_box.hpp"
#include "frame_buffer.hpp"
#include "pair.hpp"
#include "point_modifier.hpp"
#include "transfer_function.hpp"
#include "util.hpp"
#include "vector.hpp"

class Caster {
public:
	Caster(
		AABoundingBox *bounding_box, TransferFunction *transfer_function, PointModifier *modifier, double sample_step,
		Colour background_colour);
	Caster(const Caster &other);

	virtual ~Caster();

	virtual Colour cast(const Vector &ray_origin, const Vector &ray_direction);
	virtual bool cast_intersect(Vector &ray_origin, Vector &ray_direction, Pair p);

	friend void swap(Caster &first, Caster &second);
	Caster &operator=(Caster other);

protected:
	AABoundingBox *bounding_box_;
	TransferFunction *transfer_function_;
	PointModifier *modifier_;
	double sample_step_;
	Colour background_colour_;
};
