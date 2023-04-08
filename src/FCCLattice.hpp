#ifndef FCC_LATTICE_H
#define FCC_LATTICE_H

#include "Lattice.hpp"

class FCCLattice : public Lattice {
 public:
  FCCLattice(Vector min_coord, Vector max_coord, Vector resolution,
             Interpolator *interpolator);
  FCCLattice(const FCCLattice &other);

  ~FCCLattice();

  bool preprocess();
  bool load(std::string file_path);
  bool load(Matrix3D cc0, Matrix3D cc1, Matrix3D cc2, Matrix3D cc3);
  double intersect(const Vector &position) const;
  Matrix3D &raw_data();

  friend void swap(FCCLattice &first, FCCLattice &second);
  FCCLattice &operator=(FCCLattice other);

 private:
  Matrix3D mat_;
};

#endif
