#include "sblock.h"

Sblock::Sblock(bool isHeavy, Grid *g): isHeavy{isHeavy}, g{g} {
	Coord x1{2,2};
	Coord x2{1,2};
	Coord x3{1,3};
	Coord x4{0,3};
	coords = {x1,x2,x3,x4};
};

void Sblock::left() {
	Coord x1{coords.x1.x-1,coords.x1.y};
	Coord x2{coords.x2.x-1,coords.x2.y};
	Coord x3{coords.x3.x-1,coords.x3.y};
	Coord x4{coords.x4.x-1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ');
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name);
	}
}

void Sblock::right() {
	Coord x1{coords.x1.x+1,coords.x1.y};
	Coord x2{coords.x2.x+1,coords.x2.y};
	Coord x3{coords.x3.x+1,coords.x3.y};
	Coord x4{coords.x4.x+1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ');
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name);
	}
}

void Sblock::down() {
	Coord x1{coords.x1.x,coords.x1.y+1};
	Coord x2{coords.x2.x,coords.x2.y+1};
	Coord x3{coords.x3.x,coords.x3.y+1};
	Coord x4{coords.x4.x,coords.x4.y+1};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ');
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name);
	}
}

void Sblock::counterclockwise() {
	Coord x1 = {coords.x1.x-1,coords.x1.y-1};
	Coord x2 = {coords.x2.x,coords.x2.y};
	Coord x3 = {coords.x3.x+1,coords.x3.y-1};
	Coord x4 = {coords.x4.x+2,coords.x4.y};

	Coord altx1 = {coords.x1.x+1,coords.x1.y+1};
	Coord altx2 = {coords.x2.x,coords.x2.y};
	Coord altx3 = {coords.x3.x-1,coords.x3.y+1};
	Coord altx4 = {coords.x4.x-2,coords.x4.y};

	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	} else {
		temp = {altx1,altx2,altx3,altx4};
		tempOrientation  = 0;
	}
	g->update(coords, ' ');
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name);
	}
}

void Sblock::clockwise() {
	counterclockwise();
}

void Sblock::drop() {
	Coord x1 = {coords.x1.x,coords.x1.y+1};
	Coord x2 = {coords.x2.x,coords.x2.y+1};
	Coord x3 = {coords.x3.x,coords.x3.y+1};
	Coord x4 = {coords.x4.x,coords.x4.y+1};

	g->update(coords, ' ');
	BlockCoord temp = {x1,x2,x3,x4};
	if (g->check(temp)){
		while (g->check(temp)) {
			down();
			x1 = {coords.x1.x, (coords.x1.y + 1)};
			x2 = {coords.x2.x, (coords.x2.y + 1)};
			x3 = {coords.x3.x, (coords.x3.y + 1)};
			x4 = {coords.x4.x, (coords.x4.y + 1)};
			temp = {x1,x2,x3,x4};
		}
	} else{
		g->update(coords, name);
	}
}

BlockCoord Sblock::getBlockCoord() { return coords; }

char Sblock::getBlockType() { return name; }
