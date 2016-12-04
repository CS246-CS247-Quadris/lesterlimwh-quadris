#include "oblock.h"

Oblock::Oblock(bool isHeavy, Grid *g, int levelCreated): isHeavy{isHeavy}, g{g}, levelCreated{levelCreated} {
	Coord x1 = {0,14};
	Coord x2 = {1,14};
	Coord x3 = {0,13};
	Coord x4 = {1,13};
	coords = {x1,x2,x3,x4}; // initialize default coords for an Oblock
}

void Oblock::left(){
	Coord x1 = {(coords.x1.x - 1), coords.x1.y};
	Coord x2 = {(coords.x2.x - 1), coords.x2.y};
	Coord x3 = {(coords.x3.x - 1), coords.x3.y};
	Coord x4 = {(coords.x4.x - 1), coords.x4.y};

	BlockCoord temp = {x1,x2,x3,x4}; 
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);
	}
}

void Oblock::right(){
	Coord x1 = {(coords.x1.x + 1), coords.x1.y};
	Coord x2 = {(coords.x2.x + 1), coords.x2.y};
	Coord x3 = {(coords.x3.x + 1), coords.x3.y};
	Coord x4 = {(coords.x4.x + 1), coords.x4.y};

	BlockCoord temp = {x1,x2,x3,x4}; 
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);
	}
}

void Oblock::down() {
	Coord x1 = {coords.x1.x, (coords.x1.y - 1)};
	Coord x2 = {coords.x2.x, (coords.x2.y - 1)};
	Coord x3 = {coords.x3.x, (coords.x3.y - 1)};
	Coord x4 = {coords.x4.x, (coords.x4.y - 1)};
	
	BlockCoord temp = {x1,x2,x3,x4}; 
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);
	}
}

void Oblock::counterclockwise() {
	if (isHeavy){
		down();
	}
}

void Oblock::clockwise() {
	if (isHeavy){
		down();
	}
}

void Oblock::drop() {
	Coord x1 = {coords.x1.x, (coords.x1.y - 1)};
	Coord x2 = {coords.x2.x, (coords.x2.y - 1)};
	Coord x3 = {coords.x3.x, (coords.x3.y - 1)};
	Coord x4 = {coords.x4.x, (coords.x4.y - 1)};

	g->update(coords, ' ', 0, true);
	BlockCoord temp = {x1,x2,x3,x4};
	if (g->check(temp)){
		while (g->check(temp)) {
			down();
			x1 = {coords.x1.x, (coords.x1.y - 1)};
			x2 = {coords.x2.x, (coords.x2.y - 1)};
			x3 = {coords.x3.x, (coords.x3.y - 1)};
			x4 = {coords.x4.x, (coords.x4.y - 1)};
			temp = {x1,x2,x3,x4};
		}
	} else{
		g->update(coords, name, levelCreated, false);
	}
}

BlockCoord Oblock::getBlockCoord() { return coords; }

bool Oblock::getHeavy() { return isHeavy; }

char Oblock::getBlockType() { return name; }
