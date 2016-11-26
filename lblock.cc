#include "lblock.h"

Lblock::Lblock(bool isHeavy, Grid *g): isHeavy{isHeavy}, g{g}{
	Coord x1 = {2,3};
	Coord x2 = {2,4};
	Coord x3 = {1,4};
	Coord x4 = {0,4};
	coords = {x1,x2,x3,x4}; // initialize default coords for a Lblock
}

void Lblock::left(){
	Coord x1 = {(coords.x1.x - 1), coords.x1.y};
	Coord x2 = {(coords.x2.x - 1), coords.x2.y};
	Coord x3 = {(coords.x3.x - 1), coords.x3.y};
	Coord x4 = {(coords.x4.x - 1), coords.x4.y};

	BlockCoord temp = {x1,x2,x3,x4}; 
	if (g->check(temp)){
		coords = temp;
	}

	if (isHeavy){
		down();
	}
}

void Lblock::right(){
	Coord x1 = {(coords.x1.x + 1), coords.x1.y};
	Coord x2 = {(coords.x2.x + 1), coords.x2.y};
	Coord x3 = {(coords.x3.x + 1), coords.x3.y};
	Coord x4 = {(coords.x4.x + 1), coords.x4.y};

	BlockCoord temp = {x1,x2,x3,x4}; 
	if (g->check(temp)){
		coords = temp;
	}

	if (isHeavy){
		down();
	}
}

void Lblock::down() {
	Coord x1 = {coords.x1.x, (coords.x1.y + 1)};
	Coord x2 = {coords.x2.x, (coords.x2.y + 1)};
	Coord x3 = {coords.x3.x, (coords.x3.y + 1)};
	Coord x4 = {coords.x4.x, (coords.x4.y + 1)};

	BlockCoord temp = {x1,x2,x3,x4}; 
	if (g->check(temp)){
		coords = temp;
	}
}

void Lblock::counterclockwise() {
	int tempOrientation = orientation;
	BlockCoord temp;

	if (orientation == 0){
		Coord x1 = {coords.x1.x, coords.x1.y + 2};
		Coord x2 = {coords.x2.x + 1, coords.x2.y + 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x - 1, coords.x4.y - 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	}

	if (orientation == 1){
		Coord x1 = {coords.x1.x - 2, coords.x1.y};
		Coord x2 = {coords.x2.x - 1, coords.x2.y + 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x + 1, coords.x4.y - 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	if (orientation == 2){
		Coord x1 = {coords.x1.x, coords.x1.y - 2};
		Coord x2 = {coords.x2.x - 1, coords.x2.y - 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x - 1, coords.x4.y - 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	}

	if (orientation == 3){
		Coord x1 = {coords.x1.x + 2, coords.x1.y};
		Coord x2 = {coords.x2.x + 1, coords.x2.y - 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x - 1, coords.x4.y + 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 2;
	}

	if (g->check(temp)){
		coords = temp;
		orientation = tempOrientation;
	}

	if (isHeavy){
		down();
	}
}

void Lblock::clockwise() {
	int tempOrientation = orientation;
	BlockCoord temp;

	if (orientation == 0){
		Coord x1 = {coords.x1.x, coords.x1.y + 2};
		Coord x2 = {coords.x2.x + 1, coords.x2.y + 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x + 1, coords.x4.y - 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	}

	if (orientation == 1){
		Coord x1 = {coords.x1.x - 2, coords.x1.y};
		Coord x2 = {coords.x2.x - 1, coords.x2.y - 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x + 1, coords.x4.y + 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 2;
	}

	if (orientation == 2){
		Coord x1 = {coords.x1.x, coords.x1.y - 2};
		Coord x2 = {coords.x2.x + 1, coords.x2.y - 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x - 1, coords.x4.y + 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	}

	if (orientation == 3){
		Coord x1 = {coords.x1.x + 2, coords.x1.y};
		Coord x2 = {coords.x2.x + 1, coords.x2.y + 1};
		Coord x3 = {coords.x3.x, coords.x3.y};
		Coord x4 = {coords.x4.x - 1, coords.x4.y - 1};
		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	if (g->check(temp)){
		coords = temp;
		orientation = tempOrientation;
	}

	if (isHeavy){
		down();
	}
}

void Lblock::drop() {
	Coord x1 = {coords.x1.x, (coords.x1.y + 1)};
	Coord x2 = {coords.x2.x, (coords.x2.y + 1)};
	Coord x3 = {coords.x3.x, (coords.x3.y + 1)};
	Coord x4 = {coords.x4.x, (coords.x4.y + 1)};

	BlockCoord temp = {x1,x2,x3,x4}; 
	while (g->check(temp)){
		down(); // effect: coords will be updated
		x1 = {coords.x1.x, (coords.x1.y + 1)};
		x2 = {coords.x2.x, (coords.x2.y + 1)};
		x3 = {coords.x3.x, (coords.x3.y + 1)};
		x4 = {coords.x4.x, (coords.x4.y + 1)};
		temp = {x1,x2,x3,x4};
	}
}

BlockCoord Lblock::getBlockCoord() { return coords; }

char Lblock::getBlockType() const { return name; }
