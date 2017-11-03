#include "Caster.hpp"

#include <cmath>
#include "Vector4.hpp"

Caster::Caster(AABoundingBox *bounding_box, 
	TransferFunction *transfer_function, PointModifier *modifier,
	double sample_step, Colour background_colour)
: bounding_box_(bounding_box), 
transfer_function_(transfer_function), 
modifier_(modifier), 
sample_step_(sample_step), 
background_colour_(background_colour) {
	
}

Caster::Caster(const Caster &other)
: bounding_box_(other.bounding_box_), 
transfer_function_(other.transfer_function_), 
modifier_(other.modifier_),
sample_step_(other.sample_step_), 
background_colour_(other.background_colour_) {

}

Caster::~Caster() {
	delete bounding_box_;
	delete transfer_function_;
	delete modifier_;
}

Colour Caster::cast(Vector &ray_origin, Vector &ray_direction) {
	Vector ray_start, ray_end;

	if (bounding_box_->hit(ray_origin, ray_direction, ray_start, ray_end)) {
		// change ray_end and ray_start to model coordinates, 
		// saves having to map individually then
		Vector ray_position = ray_start.map_range(bounding_box_->bboxmin, 
			bounding_box_->bboxmax, bounding_box_->lattice->min_coord_, 
			bounding_box_->lattice->max_coord_);
		Vector ray_end_mapped = ray_end.map_range(bounding_box_->bboxmin, 
			bounding_box_->bboxmax, bounding_box_->lattice->min_coord_, 
			bounding_box_->lattice->max_coord_);

		double length = ray_position.distance(ray_end_mapped);

		// flip z ray direction so that it's in model coorindates
		ray_direction.z = -ray_direction.z;
	
		Vector4 dst_rgba;

		int iterations = ceil(length / sample_step_);

		for (int i = 0; i < iterations; ++i) {
			double density = bounding_box_->intersect(ray_position);

			// apply the transfer function
			Vector4 src_rgba = transfer_function_->sample_rgba_d(density);

			// pass to any modifiers that may alter colour
			Matrix3D &mat = bounding_box_->lattice->raw_data();
			modifier_->modify(mat, ray_direction, ray_position, src_rgba);

			// associate colours with alpha
			src_rgba.associate_colour(src_rgba.w);

			// volume rendering integral
			dst_rgba = (1.0 - dst_rgba.w) * src_rgba + dst_rgba;

			// get the next sample point
			ray_position += ray_direction * sample_step_;
		}
		
		// combine the ray colour with the background colour
		Colour c = {
			((background_colour_.red*(1.0-dst_rgba.w)) + (dst_rgba.x*255)),
			((background_colour_.green*(1.0-dst_rgba.w)) + (dst_rgba.y*255)),
			((background_colour_.blue*(1.0-dst_rgba.w)) + (dst_rgba.z*255)),
			dst_rgba.w*255
		};

		return c;
	}

	return background_colour_;
	
}

bool Caster::cast_intersect(Vector &ray_origin, Vector &ray_direction, 
	Pair p) {
	Vector ray_start, ray_end;
	if (bounding_box_->hit(ray_origin, ray_direction, ray_start, ray_end)) {
		Vector ray_start_mapped = ray_start.map_range(bounding_box_->bboxmin, 
			bounding_box_->bboxmax, bounding_box_->lattice->min_coord_, 
			bounding_box_->lattice->max_coord_);

		ray_direction.z = -ray_direction.z;

		double t1, t2;
		bool intersect_n1 = p.node1.intersect(ray_start_mapped, ray_direction, 
			t1, t2);
		bool intersect_n2 = p.node2.intersect(ray_start_mapped, ray_direction, 
			t1, t2);

		return intersect_n1 || intersect_n2;
	}

	return false;
}

void swap(Caster &first, Caster &second) {
	using std::swap;
	swap(first.bounding_box_, second.bounding_box_);
	swap(first.transfer_function_, second.transfer_function_);
	swap(first.modifier_, second.modifier_);
	swap(first.sample_step_, second.sample_step_);
	swap(first.background_colour_, second.background_colour_);
}

Caster& Caster::operator= (Caster other) {
	swap(*this, other);
	return *this;
}