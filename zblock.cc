#include "zblock.h"

Zblock::Zblock(bool isHeavy, Grid *g): isHeavy{isHeavy}, g{g}{
	Coord x1 = {0,3};
	Coord x2 = {1,3};
	Coord x3 = {1,4};
	Coord x4 = {2,4};
	coords = {x1,x2,x3,x4}; // initialize default coords for a Zblock
}

void Zblock::left(){
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

void Zblock::right(){
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

void Zblock::down() {
	Coord x1 = {coords.x1.x, (coords.x1.y + 1)};
	Coord x2 = {coords.x2.x, (coords.x2.y + 1)};
	Coord x3 = {coords.x3.x, (coords.x3.y + 1)};
	Coord x4 = {coords.x4.x, (coords.x4.y + 1)};

	BlockCoord temp = {x1,x2,x3,x4}; 
	if (g->check(temp)){
		coords = temp;
	}
}

void Zblock::counterclockwise() {
	int tempOrientation = orientation;
	if (orientation == 0){
		Coord x1 = {coords.x1.x, coords.x1.y + 1};
		Coord x2 = {coords.x2.x - 1, coords.x2.y};
		Coord x3 = {coords.x3.x, coords.x3.y - 1};
		Coord x4 = {coords.x4.x - 1, coords.x4.y - 2};
		BlockCoord temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	}

	if (orientation == 1){
		Coord x1 = {coords.x1.x, coords.x1.y - 1};
		Coord x2 = {coords.x2.x + 1, coords.x2.y};
		Coord x3 = {coords.x3.x, coords.x3.y + 1};
		Coord x4 = {coords.x4.x + 1, coords.x4.y + 2};
		BlockCoord temp = {x1,x2,x3,x4};
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

void Zblock::clockwise() {
	counterclockwise(); // clockwise and counterclockwise are the same
}

void Zblock::drop() {
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