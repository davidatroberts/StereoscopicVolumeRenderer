#include "Pair.hpp"

Pair::Pair(Sphere node1, Sphere node2, bool linked)
: linked(linked), node1(node1), node2(node2) {

}

void Pair::add_position(int x, int y, Colour col) {
	PairFrag frag = {
		x,
		y,
		col
	};
	position_list.push_back(frag);
}

std::ostream& operator<<(std::ostream &strm, const Pair &p) {
	return strm << "node1: " << p.node1 << " node2: " << p.node2;
}