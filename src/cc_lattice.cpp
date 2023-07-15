#include "cc_lattice.hpp"

#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

#include "util.hpp"

CCLattice::CCLattice(Vector min_coord, Vector max_coord, Vector resolution, Interpolator *interpolator)
	: Lattice(min_coord, max_coord, resolution, interpolator),
	  mat_(Matrix3D(resolution_.x, resolution_.y, resolution_.z)) {}

CCLattice::CCLattice(const CCLattice &other) : Lattice(other), mat_(other.mat_) {}

CCLattice::~CCLattice() {}

bool CCLattice::preprocess() {
	return true;
}

bool CCLattice::load(std::string file_path) {
	std::ifstream file(file_path.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!file) {
		return false;
	}

	const int data_size = resolution_.x * resolution_.y * resolution_.z;
	const int interleave = 1;

	float *datacc0 = new float[data_size];
	Util::read_short_file_as_float(file, datacc0, data_size);
	Vector offset(0, 0, 0);
	interleave_to_matrix(datacc0, mat_, offset, interleave);
	delete[] datacc0;

	file.close();
	return true;
}

bool CCLattice::load(Matrix3D &cc0) {
	mat_ = cc0;
	return true;
}

double CCLattice::intersect(const Vector &position) const {
	Vector pos = position.map_range(min_coord_, max_coord_, min_coord_, volume_limit_);
	return interpolator_->interpolate(pos, mat_);
}

Matrix3D &CCLattice::raw_data() {
	return mat_;
}

void swap(CCLattice &first, CCLattice &second) {
	using std::swap;
	swap(first.max_coord_, second.max_coord_);
	swap(first.resolution_, second.resolution_);
	swap(first.mat_, second.mat_);
}

CCLattice &CCLattice::operator=(CCLattice other) {
	swap(*this, other);
	return *this;
}
