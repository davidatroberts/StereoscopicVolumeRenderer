#include "vector4.hpp"

Vector4::Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(const Colour &col) : x(col.red), y(col.green), z(col.blue), w(col.alpha) {}
