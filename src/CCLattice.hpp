#ifndef CC_LATTICE_H
#define CC_LATTICE_H

#include "Lattice.hpp"

class CCLattice: public Lattice {
public:
	CCLattice(Vector min_coord, Vector max_coord, Vector resolution, Interpolator *interpolator);
	CCLattice(const CCLattice &other);

	~CCLattice();

	bool preprocess();
	bool load(std::string file_path);
	bool load(Matrix3D &cc0);
	double intersect(Vector &position);
	Matrix3D& raw_data();

	friend void swap(CCLattice &first, CCLattice &second);
	CCLattice& operator= (CCLattice other);

private:
	Matrix3D mat_;
};

#endif