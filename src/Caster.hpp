#ifndef CASTER_H
#define CASTER_H 

#include "AABoundingBox.hpp"
#include "Vector.hpp"
#include "TransferFunction.hpp"
#include "FrameBuffer.hpp"
#include "PointModifier.hpp"
#include "Pair.hpp"
#include "Util.hpp"

class Caster {
public:
	Caster(AABoundingBox *bounding_box, TransferFunction *transfer_function,
		PointModifier *modifier, double sample_step, Colour background_colour);
	Caster(const Caster &other);

	virtual ~Caster();
	
	virtual Colour cast(Vector &ray_origin, Vector &ray_direction);
	virtual bool cast_intersect(Vector &ray_origin, Vector &ray_direction, 
		Pair p);

	friend void swap(Caster &first, Caster &second);
	Caster& operator= (Caster other);

protected:
	AABoundingBox *bounding_box_;
	TransferFunction *transfer_function_;
	PointModifier *modifier_;
	double sample_step_;
	Colour background_colour_;
};

#endif