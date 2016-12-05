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

bool Sblock::getHeavy() { return isHeavy; }

char Sblock::getBlockType() { return name; }

int Sblock::lowestRowCoord() {
	int lowest = 20;
	if (coords.x1.y < lowest) {
		lowest = coords.x1.y;
	}
	if (coords.x2.y < lowest) {
		lowest = coords.x2.y;
	}
	if (coords.x3.y < lowest) {
		lowest = coords.x3.y;
	}
	if (coords.x4.y < lowest) {
		lowest = coords.x4.y;
	}
	return lowest;
}

int Sblock::numBlocksInLowest(int row) {
	int num = 0;
	if (coords.x1.y == row) {
		num++;
	}
	if (coords.x2.y == row) {
		num++;
	}
	if (coords.x3.y == row) {
		num++;
	}
	if (coords.x4.y == row) {
		num++;
	}
	return num;
}

BlockCoord Sblock::hint() {
	int lowestRow = 20;
	int currCol;
	int currOrien;
	int startOrien = orientation;
	int blocksInLowest = 0;  //Amount of blocks in lowest row
	Coord x1 = {coords.x1.x,coords.x1.y};
	Coord x2 = {coords.x2.x,coords.x2.y};
	Coord x3 = {coords.x3.x,coords.x3.y};
	Coord x4 = {coords.x4.x,coords.x4.y};
	const BlockCoord start = {x1,x2,x3,x4};  //start coords in order to reset after determining hint

	BlockCoord best;

	BlockCoord curr;

	for (int orien = 0; orien < 4; orien++) {
		std::cout << "orientation is: " << orientation << std::endl;
		for (int i = 0; i <= 10; ++i) {
			Coord cx1 = {coords.x1.x,coords.x1.y};
			Coord cx2 = {coords.x2.x,coords.x2.y};
			Coord cx3 = {coords.x3.x,coords.x3.y};
			Coord cx4 = {coords.x4.x,coords.x4.y};
			curr = {cx1,cx2,cx3,cx4};
			drop();
			if (lowestRowCoord() < lowestRow) {
				lowestRow = lowestRowCoord();
				std::cout << "lowestRow is: " << lowestRow << std::endl;
				best = coords;
			} 
			if (numBlocksInLowest(lowestRow) > blocksInLowest) {
				blocksInLowest = numBlocksInLowest(lowestRow);
				std::cout << "numBlocksInLowest is: " << blocksInLowest << std::endl;
				best = coords;
			}
			coords = curr;
			right();
			g->update(coords, ' ', 0, true);
		}
		for (int i = 10; i >= 0; --i) {
			Coord cx1 = {coords.x1.x,coords.x1.y};
			Coord cx2 = {coords.x2.x,coords.x2.y};
			Coord cx3 = {coords.x3.x,coords.x3.y};
			Coord cx4 = {coords.x4.x,coords.x4.y};
			curr = {cx1,cx2,cx3,cx4};
			drop();
			if (lowestRowCoord() < lowestRow) {
				lowestRow = lowestRowCoord();
				blocksInLowest = numBlocksInLowest(lowestRow);
				best = coords;
			} 
			if (numBlocksInLowest(lowestRow) > blocksInLowest) {
				blocksInLowest = numBlocksInLowest(lowestRow);
				best = coords;
			}
			coords = curr;
			left();
			g->update(coords, ' ', 0, true);
		}				
		clockwise();
		g->update(coords, ' ', 0, true);
	}
	orientation = startOrien;
	coords = start;
	g->update(coords, name, levelCreated, false);
	return best;
}