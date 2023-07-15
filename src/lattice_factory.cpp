#include "lattice_factory.hpp"

#include "cc_lattice.hpp"
#include "bcc_lattice.hpp"
#include "fcc_lattice.hpp"

LatticeFactory::LatticeFactory(Vector min_coord, Vector max_coord, Vector resolution, 
	Interpolator *interpolator)
: min_coord_(min_coord), max_coord_(max_coord), resolution_(resolution), interpolator_(interpolator) {

}

LatticeFactory::~LatticeFactory() {
	delete interpolator_;
}

Lattice* LatticeFactory::make_lattice(LatticeType type) {
	switch (type) {
		case LatticeType::CC:
			return new CCLattice(min_coord_, max_coord_, resolution_, interpolator_);
			break;
		case LatticeType::BCC:
			resolution_*=2;
			return new BCCLattice(min_coord_, max_coord_, resolution_, interpolator_);
			break;
		case LatticeType::FCC:
			resolution_*=2;
			return new FCCLattice(min_coord_, max_coord_, resolution_, interpolator_);
			break;
		default:
			return NULL;
			break;
	}
}
