#ifndef PAIR_H
#define PAIR_H

#include <map>

#include "sphere.hpp"
#include "util.hpp"

typedef struct {
	int x;
	int y;
	Colour col;
} PairFrag;

class Pair
{
public:
	Pair(Sphere node1=Sphere(), Sphere node2=Sphere(), bool linked=false);

	void add_position(int x, int y, Colour col);

	friend std::ostream& operator<<(std::ostream&, const Pair &p);

	bool linked;
	Sphere node1, node2;
	std::vector<PairFrag> position_list;
};

#endif