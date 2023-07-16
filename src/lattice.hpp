#pragma once

#include <cmath>
#include <fstream>
#include <string>

#include "interpolator.hpp"
#include "matrix_3d.hpp"
#include "vector.hpp"

class Lattice {
 public:
  Lattice(Vector min_coord_, Vector max_coord, Vector resolution,
          Interpolator *interpolator);
  Lattice(const Lattice &other);

  virtual ~Lattice() { delete interpolator_; }

  void interleave_to_matrix(float *data, Matrix3D &mat, Vector offset,
                            int interleave);
  virtual bool preprocess() = 0;
  virtual bool load(std::string file_path) = 0;
  virtual double intersect(const Vector &mapped) const = 0;
  virtual Matrix3D &raw_data() = 0;

  Vector min_coord_;
  Vector max_coord_;

 protected:
  Vector resolution_;
  Vector volume_limit_;
  Interpolator *interpolator_;
};
