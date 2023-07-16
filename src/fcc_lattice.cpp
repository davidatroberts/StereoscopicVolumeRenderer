#include "fcc_lattice.hpp"

#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

#include "util.hpp"

FCCLattice::FCCLattice(Vector min_coord, Vector max_coord, Vector resolution, Interpolator *interpolator)
	: Lattice(min_coord, max_coord, resolution, interpolator),
	  mat_(Matrix3D(resolution_.x * 2, resolution_.y * 2, resolution_.z * 2)) {}

FCCLattice::FCCLattice(const FCCLattice &other) : Lattice(other), mat_(other.mat_) {}

FCCLattice::~FCCLattice() {}

bool FCCLattice::preprocess() {
	// set up the discrete filter we're going to use
	std::vector<float> mask_vals = {0.0, 0.0,       0.0, 0.0,       1.0 / 6.0, 0.0,       0.0, 0.0,       0.0,
									0.0, 1.0 / 6.0, 0.0, 1.0 / 6.0, 1.0,       1.0 / 6.0, 0.0, 1.0 / 6.0, 0.0,
									0.0, 0.0,       0.0, 0.0,       1.0 / 6.0, 0.0,       0.0, 0.0,       0.0};
	Matrix3D mask(mask_vals, 3, 3, 3);

	bool err;
	mat_ = mat_.convolve(mask, err);

	return !err;
}

bool FCCLattice::load(std::string file_path) {
	std::ifstream file(file_path.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!file) {
		return false;
	}

	int data_size = (resolution_.x / 2) * (resolution_.y / 2) * (resolution_.z / 2);
	const int interleave = 2;

	// load cc0
	float *datacc0 = new float[data_size];
	Util::read_short_file_as_float(file, datacc0, data_size);
	interleave_to_matrix(datacc0, mat_, Vector(0, 0, 0), interleave);
	delete[] datacc0;

	// load cc1
	float *datacc1 = new float[data_size];
	Util::read_short_file_as_float(file, datacc1, data_size);
	interleave_to_matrix(datacc1, mat_, Vector(1, 1, 0), interleave);
	delete[] datacc1;

	// load cc2
	float *datacc2 = new float[data_size];
	Util::read_short_file_as_float(file, datacc2, data_size);
	interleave_to_matrix(datacc2, mat_, Vector(1, 0, 1), interleave);
	delete[] datacc2;

	// load cc3
	float *datacc3 = new float[data_size];
	Util::read_short_file_as_float(file, datacc3, data_size);
	interleave_to_matrix(datacc0, mat_, Vector(0, 1, 1), interleave);
	delete[] datacc3;

	file.close();
	return true;
}

bool FCCLattice::load(Matrix3D cc0, Matrix3D cc1, Matrix3D cc2, Matrix3D cc3) {
	return false;
}

double FCCLattice::intersect(const Vector &position) const {
	Vector pos = position.map_range(min_coord_, max_coord_, min_coord_, volume_limit_);
	return interpolator_->interpolate(pos, mat_);
}

Matrix3D &FCCLattice::raw_data() {
	return mat_;
}

void swap(FCCLattice &first, FCCLattice &second) {
	using std::swap;
	swap(first.max_coord_, second.max_coord_);
	swap(first.resolution_, second.resolution_);
	swap(first.mat_, second.mat_);
}
