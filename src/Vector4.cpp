#include "Vector4.hpp"

Vector4::Vector4(double x, double y, double z, double w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Colour col) {
	x = col.red;
	y = col.green;
	z = col.blue;
	w = col.alpha;
}

Vector4::Vector4() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->w = 0.0;
}