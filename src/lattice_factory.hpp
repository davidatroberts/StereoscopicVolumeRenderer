#pragma once

#include <string>

#include "vector.hpp"
#include "settings.hpp"
#include "lattice.hpp"
#include "interpolator.hpp"

class LatticeFactory {
public:
	LatticeFactory(Vector min_coord, Vector max_coord, Vector resolution, Interpolator *interpolator);

	~LatticeFactory();

	Lattice* make_lattice(LatticeType type);

private:
	Vector min_coord_;
	Vector max_coord_;
	Vector resolution_;
	Interpolator *interpolator_;
};
