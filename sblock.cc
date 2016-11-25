#include "sblock.h"
using namespace std;

Sblock::Sblock(bool isHeavy, Grid *g): isHeavy{isHeavy}, g{g} {
	Coord x1{2,2};
	Coord x2{1,2};
	Coord x3{1,3};
	Coord x4{0,3};
	BlockCoord coords{x1,x2,x3,x4};
};

void Sblock::left() {
	Coord x1{coords.x1.x-1,coords.x1.y};
	Coord x2{coords.x2.x-1,coords.x2.y};
	Coord x3{coords.x3.x-1,coords.x3.y};
	Coord x4{coords.x4.x-1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	if (g->check(temp)) {
		coords = temp;
	}
}

void Sblock::right() {
	Coord x1{coords.x1.x+1,coords.x1.y};
	Coord x2{coords.x2.x+1,coords.x2.y};
	Coord x3{coords.x3.x+1,coords.x3.y};
	Coord x4{coords.x4.x+1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	if (g->check(temp)) {
		coords = temp;
	}
}

void Sblock::down() {
	Coord x1{coords.x1.x,coords.x1.y+1};
	Coord x2{coords.x2.x,coords.x2.y+1};
	Coord x3{coords.x3.x,coords.x3.y+1};
	Coord x4{coords.x4.x,coords.x4.y+1};

	BlockCoord temp{x1,x2,x3,x4};
	if (g->check(temp)) {
		coords = temp;
	}
}

void Sblock::counterclockwise() {
	Coord x1{coords.x1.x-1,coords.x1.y-1};
	Coord x2{coords.x2.x,coords.x2.y};
	Coord x3{coords.x3.x+1,coords.x3.y-1};
	Coord x4{coords.x4.x+2,coords.x4.y};

	Coord altx1{coords.x1.x+1,coords.x1.y+1};
	Coord altx2{coords.x2.x,coords.x2.y};
	Coord altx3{coords.x3.x-1,coords.x3.y+1};
	Coord altx4{coords.x4.x-2,coords.x4.y};

	int temporientation;

	if (orientation == 0) {
		BlockCoord temp{x1,x2,x3,x};
		temporientation = 1;
	} else {
		BlockCoord temp{altx1,altx2,altx3,altx4};
		temporientation  = 0;
	}
	if (g->check(temp)) {
		coords = temp;
		orientation = temporientation;
	} 
}

void Sblock::clockwise() {
	counterclockwise();
}

void Sblock::drop() {
	Coord x1{coords.x1.x,coords.x1.y+1};
	Coord x2{coords.x2.x,coords.x2.y+1};
	Coord x3{coords.x3.x,coords.x3.y+1};
	Coord x4{coords.x4.x,coords.x4.y+1};

	BlockCoord temp{x1,x2,x3,x4};
	while (g->check(temp)) {
		down();
		temp = {coord.x1.x,coord.x1.y+1,coord.x2.x,coord.x2.y+1,coord.x3.x,coord.x3.y+1,coord.x4.x,x4.y+1};
	}
}