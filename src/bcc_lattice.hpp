#ifndef BCC_LATTICE_H
#define BCC_LATTICE_H

#include "lattice.hpp"

class BCCLattice : public Lattice {
public:
	BCCLattice(Vector min_coord, Vector max_coord, Vector resolution, Interpolator *interpolator);
	BCCLattice(const BCCLattice &other);

	~BCCLattice();

	bool preprocess();
	bool load(std::string file_path);
	bool load(Matrix3D &cc0, Matrix3D &cc1);
	double intersect(const Vector &position) const;
	Matrix3D &raw_data();

	friend void swap(BCCLattice &first, BCCLattice &second);
	BCCLattice &operator=(BCCLattice other);

private:
	Matrix3D mat_;
};

#endif
