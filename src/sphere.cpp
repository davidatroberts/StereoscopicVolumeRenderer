#include "sphere.hpp"

#include "util.hpp"

Sphere::Sphere(Vector centre, double radius)
: centre_(centre), radius_(radius) {

}

bool Sphere::intersect(Vector &ray_origin, Vector &ray_direction, double &t1, double &t2) {
	Vector q = ray_origin - centre_;
	double a = ray_direction.dot(ray_direction);
	
	Vector tmp = q * 2.0;
	double b = tmp.dot(ray_direction);
	double c = q.dot(q) - (radius_ * radius_);

	bool hit = Util::solve_quad(a, b, c, t1, t2);

	if (hit) {
		if ((t1 <= 0.0) && (t2 > 0.0)) {
			t1 = HUGE_VAL;
			return true;
		}
		else {
			if ((t1 <= 0.0) && (t2 <= 0.0)) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		return false;
	}	
}

std::ostream& operator<<(std::ostream &strm, const Sphere &sp) {
  return strm << "centre(" << sp.centre_.x << ", " << sp.centre_.y << ", " << sp.centre_.z << ")";
}