#include "AABoundingBox.hpp"

AABoundingBox::AABoundingBox(Vector bboxmin, Vector bboxmax, 
	Lattice *lattice)
: bboxmin(bboxmin), bboxmax(bboxmax), lattice(lattice) {

} 

AABoundingBox::~AABoundingBox() {

}

bool AABoundingBox::hit(Vector ray_origin, Vector ray_direction, 
	Vector &ray_start, Vector &ray_end) {
	// r.dir is unit direction vector of ray
	Vector dir_frac( 1.0f / ray_direction.x, 1.0f / ray_direction.y, 
		1.0f / ray_direction.z);
	// lb is the corner of AABB with minimal coordinates - left bottom, 
	// rt is maximal corner, r.org is origin of ray
	double t1 = (bboxmin.x - ray_origin.x)*dir_frac.x;
	double t2 = (bboxmax.x - ray_origin.x)*dir_frac.x;
	double t3 = (bboxmin.y - ray_origin.y)*dir_frac.y;
	double t4 = (bboxmax.y - ray_origin.y)*dir_frac.y;
	double t5 = (bboxmin.z - ray_origin.z)*dir_frac.z;
	double t6 = (bboxmax.z - ray_origin.z)*dir_frac.z;

	double tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), 
		std::min(t5, t6));
	double tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), 
		std::max(t5, t6));

	if (tmax < 0) {
	    return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
	    return false;
	}

	// values are returned as world coordinates
	ray_start = ray_origin + (ray_direction*tmin);
	ray_end = ray_origin + (ray_direction*tmax);

	return true;
}

double AABoundingBox::intersect(Vector &ray_position) {
	return lattice->intersect(ray_position);
}