#include "tblock.h"

Tblock::Tblock(bool isHeavy, Grid *g): isHeavy{isHeavy}, g{g} {
	Coord x1{0,16};
	Coord x2{1,16};
	Coord x3{2,16};
	Coord x4{1,15};
	coords = {x1,x2,x3,x4};
};

void Tblock::left() {
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

	if (isHeavy){
		down();
	}
}

void Tblock::right() {
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

	if (isHeavy){
		down();
	}
}

void Tblock::down() {
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

void Tblock::counterclockwise() {
	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		Coord x1{coords.x1.x+1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y-1};
		Coord x4{coords.x4.x+1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	} 
	if (orientation == 1) {
		Coord x1{coords.x1.x+1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y+1};
		Coord x4{coords.x4.x-1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation  = 2;
	}
	if (orientation == 2) {
		Coord x1{coords.x1.x-1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y+1};
		Coord x4{coords.x4.x-1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	}
	if (orientation == 3) {
		Coord x1{coords.x1.x-1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y-1};
		Coord x4{coords.x4.x+1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	g->update(coords, ' ');
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name);
	}

	if (isHeavy){
		down();
	}
}

void Tblock::clockwise() {
	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		Coord x1{coords.x1.x+1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y+1};
		Coord x4{coords.x4.x-1,coords.x4.y-1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	} 
<<<<<<< HEAD

	if (orientation == 3) {
		Coord x1{coords.x1.x+1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y-1};
		Coord x4{coords.x4.x+1,coords.x4.y-1};
=======
	if (orientation == 3) {
		Coord x1{coords.x1.x+1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y+1};
		Coord x4{coords.x4.x+1,coords.x4.y+1};
>>>>>>> 9541eddc947a0aeba0ee72ee6071d5fe3ee660a2

		temp = {x1,x2,x3,x4};
		tempOrientation  = 2;
	}
	if (orientation == 2) {
		Coord x1{coords.x1.x-1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y-1};
		Coord x4{coords.x4.x+1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	}
<<<<<<< HEAD

	if (orientation == 1) {
		Coord x1{coords.x1.x-1,coords.x1.y-1};
=======
	if (orientation == 1) {
		Coord x1{coords.x1.x-1,coords.x1.y+1};
>>>>>>> 9541eddc947a0aeba0ee72ee6071d5fe3ee660a2
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y+1};
		Coord x4{coords.x4.x-1,coords.x4.y+1};

		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	g->update(coords, ' ');
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name);
	}

	if (isHeavy){
		down();
	}

}

void Tblock::drop() {
	Coord x1 = {coords.x1.x,coords.x1.y-1};
	Coord x2 = {coords.x2.x,coords.x2.y-1};
	Coord x3 = {coords.x3.x,coords.x3.y-1};
	Coord x4 = {coords.x4.x,coords.x4.y-1};

	g->update(coords, ' ');
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
		g->update(coords, name);
	}
}

BlockCoord Tblock::getBlockCoord() { 
	/*std::cout << "Current coordinates of this block:" << std::endl;
	std::cout << "Row = " << coords.x1.y << " " << "Col = " << coords.x1.x << std::endl; 
	std::cout << "Row = " << coords.x2.y << " " << "Col = " << coords.x2.x << std::endl; 
	std::cout << "Row = " << coords.x3.y << " " << "Col = " << coords.x3.x << std::endl; 
	std::cout << "Row = " << coords.x4.y << " " << "Col = " << coords.x4.x << std::endl;*/
	return coords; 
}

char Tblock::getBlockType() { return name; }