#include "lattice.hpp"

Lattice::Lattice(Vector min_coord, Vector max_coord, Vector resolution, 
	Interpolator *interpolator)
: min_coord_(min_coord), max_coord_(max_coord), resolution_(resolution), 
interpolator_(interpolator) {
	volume_limit_ = resolution_-1;
}

Lattice::Lattice(const Lattice &other)
: max_coord_(other.max_coord_), resolution_(other.resolution_), 
interpolator_(other.interpolator_) {

}

void Lattice::interleave_to_matrix(float *data, Matrix3D &mat, Vector offset, 
	int interleave) {
	for (int z=(int)offset.z; z<resolution_.z; z+=interleave) {
		for (int y=(int)offset.y; y<resolution_.y; y+=interleave) {
			for (int x=(int)offset.x; x<resolution_.x; x+=interleave) {
				int x_index = (x-offset.x)/interleave;
				int y_index = (y-offset.y)/interleave;
				int z_index = (z-offset.z)/interleave;

				float val = data[int(x_index + (resolution_.x/interleave) * 
					(y_index + (resolution_.y/interleave) * z_index))];
				mat(x, y, z) = val;
			}
		}
	}
}