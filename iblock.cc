#include "iblock.h"

Iblock::Iblock(bool isHeavy, Grid *g): isHeavy{isHeavy}, g{g} {
	Coord x1{0,2};
	Coord x2{1,2};
	Coord x3{2,2};
	Coord x4{3,2};
	coords = {x1,x2,x3,x4};
};

void Iblock::left() {
	Coord x1{coords.x1.x-1,coords.x1.y};
	Coord x2{coords.x2.x-1,coords.x2.y};
	Coord x3{coords.x3.x-1,coords.x3.y};
	Coord x4{coords.x4.x-1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	if (g->check(temp)) {
		coords = temp;
	}
}

void Iblock::right() {
	Coord x1{coords.x1.x+1,coords.x1.y};
	Coord x2{coords.x2.x+1,coords.x2.y};
	Coord x3{coords.x3.x+1,coords.x3.y};
	Coord x4{coords.x4.x+1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	if (g->check(temp)) {
		coords = temp;
	}
}

void Iblock::down() {
	Coord x1{coords.x1.x,coords.x1.y+1};
	Coord x2{coords.x2.x,coords.x2.y+1};
	Coord x3{coords.x3.x,coords.x3.y+1};
	Coord x4{coords.x4.x,coords.x4.y+1};

	BlockCoord temp{x1,x2,x3,x4};
	if (g->check(temp)) {
		coords = temp;
	}
}

void Iblock::counterclockwise() {
	Coord x1{coords.x1.x+1,coords.x1.y+1};
	Coord x2{coords.x2.x,coords.x2.y};
	Coord x3{coords.x3.x-1,coords.x3.y-1};
	Coord x4{coords.x4.x-2,coords.x4.y-2};

	Coord altx1{coords.x1.x-1,coords.x1.y-1};
	Coord altx2{coords.x2.x,coords.x2.y};
	Coord altx3{coords.x3.x+1,coords.x3.y+1};
	Coord altx4{coords.x4.x+2,coords.x4.y+2};

	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	} else {
		temp = {altx1,altx2,altx3,altx4};
		tempOrientation  = 0;
	}
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} 
}

void Iblock::clockwise() {
	counterclockwise();
}

void Iblock::drop() {
	Coord x1 = {coords.x1.x,coords.x1.y+1};
	Coord x2 = {coords.x2.x,coords.x2.y+1};
	Coord x3 = {coords.x3.x,coords.x3.y+1};
	Coord x4 = {coords.x4.x,coords.x4.y+1};

	BlockCoord temp = {x1,x2,x3,x4};
	while (g->check(temp)) {
		down();
		x1 = {coords.x1.x, (coords.x1.y + 1)};
		x2 = {coords.x2.x, (coords.x2.y + 1)};
		x3 = {coords.x3.x, (coords.x3.y + 1)};
		x4 = {coords.x4.x, (coords.x4.y + 1)};
		temp = {x1,x2,x3,x4};
	}
}

BlockCoord Iblock::getBlockCoord() { return coords; }

char Iblock::getBlockType() const { return name; }