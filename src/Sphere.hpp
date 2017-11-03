#ifndef SPHERE_H
#define SPHERE_H

#include "Vector.hpp"

class Sphere
{
public:
	Sphere(Vector centre=Vector(0, 0, 0), double radius=0.1);

	bool intersect(Vector &ray_origin, Vector &ray_direction, double &t1, double &t2);

	friend std::ostream& operator<<(std::ostream &strm, const Sphere &sp);
private:
	Vector centre_;
	double radius_;
};

#endif