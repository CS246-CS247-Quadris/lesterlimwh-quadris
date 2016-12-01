#include "sblock.h"

Sblock::Sblock(bool isHeavy, Grid *g, int levelCreated): isHeavy{isHeavy}, g{g}, levelCreated{levelCreated}  {
	Coord x1{0,15};
	Coord x2{1,15};
	Coord x3{1,16};
	Coord x4{2,16};
	coords = {x1,x2,x3,x4};
};

void Sblock::left() {
	Coord x1{coords.x1.x-1,coords.x1.y};
	Coord x2{coords.x2.x-1,coords.x2.y};
	Coord x3{coords.x3.x-1,coords.x3.y};
	Coord x4{coords.x4.x-1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);
	}

	if (isHeavy){
		down();
	}
}

void Sblock::right() {
	Coord x1{coords.x1.x+1,coords.x1.y};
	Coord x2{coords.x2.x+1,coords.x2.y};
	Coord x3{coords.x3.x+1,coords.x3.y};
	Coord x4{coords.x4.x+1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);
	}

	if (isHeavy){
		down();
	}
}

void Sblock::down() {
	Coord x1{coords.x1.x,coords.x1.y-1};
	Coord x2{coords.x2.x,coords.x2.y-1};
	Coord x3{coords.x3.x,coords.x3.y-1};
	Coord x4{coords.x4.x,coords.x4.y-1};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);
	}
}

void Sblock::counterclockwise() {
	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		Coord x1{coords.x1.x+2,coords.x1.y};
		Coord x2{coords.x2.x+1,coords.x2.y+1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x-1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	} 
	if (orientation == 1) {
		Coord x1{coords.x1.x,coords.x1.y+2};
		Coord x2{coords.x2.x-1,coords.x2.y+1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x-1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 2;
	}
	if (orientation == 2) {
		Coord x1{coords.x1.x-2,coords.x1.y};
		Coord x2{coords.x2.x-1,coords.x2.y-1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x+1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	}
	if (orientation == 3) {
		Coord x1{coords.x1.x,coords.x1.y-2};
		Coord x2{coords.x2.x+1,coords.x2.y-1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x+1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name, levelCreated, false);
	}

	if (isHeavy){
		down();
	}
}

void Sblock::clockwise() {
	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		Coord x1{coords.x1.x,coords.x1.y+2};
		Coord x2{coords.x2.x-1,coords.x2.y+1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x-1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	} 
	if (orientation == 3) {
		Coord x1{coords.x1.x+2,coords.x1.y};
		Coord x2{coords.x2.x+1,coords.x2.y+1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x-1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation  = 2;
	}
	if (orientation == 2) {
		Coord x1{coords.x1.x,coords.x1.y-2};
		Coord x2{coords.x2.x+1,coords.x2.y-1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x+1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	}
	if (orientation == 1) {
		Coord x1{coords.x1.x-2,coords.x1.y};
		Coord x2{coords.x2.x-1,coords.x2.y-1};
		Coord x3{coords.x3.x,coords.x3.y};
		Coord x4{coords.x4.x+1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name, levelCreated, false);
	}

	if (isHeavy){
		down();
	}

}

void Sblock::drop() {
	Coord x1 = {coords.x1.x,coords.x1.y-1};
	Coord x2 = {coords.x2.x,coords.x2.y-1};
	Coord x3 = {coords.x3.x,coords.x3.y-1};
	Coord x4 = {coords.x4.x,coords.x4.y-1};

	g->update(coords, ' ', 0, true);
	BlockCoord temp = {x1,x2,x3,x4};
	if (g->check(temp)){
		while (g->check(temp)) {
			down();
			x1 = {coords.x1.x, (coords.x1.y-1)};
			x2 = {coords.x2.x, (coords.x2.y-1)};
			x3 = {coords.x3.x, (coords.x3.y-1)};
			x4 = {coords.x4.x, (coords.x4.y-1)};
			temp = {x1,x2,x3,x4};
		}
	} else{
		g->update(coords, name, levelCreated, false);
	}
}

BlockCoord Sblock::getBlockCoord() { return coords; }

char Sblock::getBlockType() { return name; }


// Pranav can you see this

