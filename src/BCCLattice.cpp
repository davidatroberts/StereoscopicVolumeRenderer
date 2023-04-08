#include "BCCLattice.hpp"

#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

#include "Util.hpp"

BCCLattice::BCCLattice(Vector min_coord, Vector max_coord, Vector resolution, Interpolator *interpolator)
	: Lattice(min_coord, max_coord, resolution, interpolator),
	  mat_(Matrix3D(resolution_.x, resolution_.y, resolution_.z)) {}

BCCLattice::BCCLattice(const BCCLattice &other) : Lattice(other), mat_(other.mat_) {}

BCCLattice::~BCCLattice() {}

bool BCCLattice::preprocess() {
	// set up the discrete filter we're going to use
	std::vector<float> mask_vals = {0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0,

									0.0, 0.5, 0.0, 0.5, 1.0, 0.5, 0.0, 0.5, 0.0,

									0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0};
	Matrix3D mask(mask_vals, 3, 3, 3);

	bool err;
	mat_ = mat_.convolve(mask, err);

	return !err;
}

bool BCCLattice::load(std::string file_path) {
	std::ifstream file(file_path.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!file) {
		return false;
	}

	const int data_size = (resolution_.x / 2) * (resolution_.y / 2) * (resolution_.z / 2);
	const int interleave = 2;

	// load the blue matrix first
	// iterate over the data and place into even positions into the matrix
	float *datacc0 = new float[data_size];
	Util::read_short_file_as_float(file, datacc0, data_size);
	interleave_to_matrix(datacc0, mat_, Vector(0, 0, 0), interleave);
	delete[] datacc0;

	// load the red matrix next
	// iterate over the data and place into odd positions in the matrix
	float *datacc1 = new float[data_size];
	Util::read_short_file_as_float(file, datacc1, data_size);
	interleave_to_matrix(datacc1, mat_, Vector(1, 1, 1), interleave);
	delete[] datacc1;

	file.close();
	return true;
}

bool BCCLattice::load(Matrix3D &cc0, Matrix3D &cc1) {
	const int interleave = 2;
	interleave_to_matrix(cc0.raw_data(), mat_, Vector(0, 0, 0), interleave);
	interleave_to_matrix(cc1.raw_data(), mat_, Vector(1, 1, 1), interleave);

	return true;
}

double BCCLattice::intersect(const Vector &position) const {
	Vector pos = position.map_range(min_coord_, max_coord_, min_coord_, volume_limit_);
	return interpolator_->interpolate(pos, mat_);
}

Matrix3D &BCCLattice::raw_data() {
	return mat_;
}

void swap(BCCLattice &first, BCCLattice &second) {
	using std::swap;
	swap(first.max_coord_, second.max_coord_);
	swap(first.resolution_, second.resolution_);
	swap(first.mat_, second.mat_);
}
