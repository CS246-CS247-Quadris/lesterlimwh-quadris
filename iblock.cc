#include "iblock.h"

Iblock::Iblock(bool isHeavy, Grid *g, int levelCreated): isHeavy{isHeavy}, g{g}, levelCreated{levelCreated} {
	Coord x1{0,15};
	Coord x2{1,15};
	Coord x3{2,15};
	Coord x4{3,15};
	coords = {x1,x2,x3,x4};  //Start coordinates for I block
};

void Iblock::left() {  //Updates the coordinates one position to the left if possible
	Coord x1{coords.x1.x-1,coords.x1.y};
	Coord x2{coords.x2.x-1,coords.x2.y};
	Coord x3{coords.x3.x-1,coords.x3.y};
	Coord x4{coords.x4.x-1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);  //If it can't go left, redraw in old place
	}
}
 
void Iblock::right() {  //Updates the coordinates one position to the right if possible
	Coord x1{coords.x1.x+1,coords.x1.y};
	Coord x2{coords.x2.x+1,coords.x2.y};
	Coord x3{coords.x3.x+1,coords.x3.y};
	Coord x4{coords.x4.x+1,coords.x4.y};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);  //If it can't go right, redraw in old place
	}

}

void Iblock::down() {  //Updates the coordinates one position down if possible
	Coord x1{coords.x1.x,coords.x1.y-1};
	Coord x2{coords.x2.x,coords.x2.y-1};
	Coord x3{coords.x3.x,coords.x3.y-1};
	Coord x4{coords.x4.x,coords.x4.y-1};

	BlockCoord temp{x1,x2,x3,x4};
	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
	} else{
		g->update(coords, name, levelCreated, false);  //If it can't go down, redraw in old place
	}
}

void Iblock::counterclockwise() {  //Rotates the block counterclockwise if possible
	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		Coord x1{coords.x1.x+1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y+1};
		Coord x4{coords.x4.x-2,coords.x4.y+2};

		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	} 
	if (orientation == 1) {
		Coord x1{coords.x1.x+1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y-1};
		Coord x4{coords.x4.x-2,coords.x4.y-2};

		temp = {x1,x2,x3,x4};
		tempOrientation  = 2;
	}
	if (orientation == 2) {
		Coord x1{coords.x1.x-1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y-1};
		Coord x4{coords.x4.x+2,coords.x4.y-2};

		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	}
	if (orientation == 3) {
		Coord x1{coords.x1.x-1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y+1};
		Coord x4{coords.x4.x+2,coords.x4.y+2};

		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name, levelCreated, false);  //If it can't rotate counterclockwise, redraw in old place
	}

	if (isHeavy){
		down();
	}
}

void Iblock::clockwise() {  //Rotates the block clockwise if possible
	int tempOrientation;
	BlockCoord temp;

	if (orientation == 0) {
		Coord x1{coords.x1.x+1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y-1};
		Coord x4{coords.x4.x-2,coords.x4.y-2};

		temp = {x1,x2,x3,x4};
		tempOrientation = 3;
	} 
	if (orientation == 3) {
		Coord x1{coords.x1.x+1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x-1,coords.x3.y+1};
		Coord x4{coords.x4.x-2,coords.x4.y+2};

		temp = {x1,x2,x3,x4};
		tempOrientation  = 2;
	}
	if (orientation == 2) {
		Coord x1{coords.x1.x-1,coords.x1.y-1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y+1};
		Coord x4{coords.x4.x+2,coords.x4.y+2};

		temp = {x1,x2,x3,x4};
		tempOrientation = 1;
	}
	if (orientation == 1) {
		Coord x1{coords.x1.x-1,coords.x1.y+1};
		Coord x2{coords.x2.x,coords.x2.y};
		Coord x3{coords.x3.x+1,coords.x3.y-1};
		Coord x4{coords.x4.x+2,coords.x4.y-2};

		temp = {x1,x2,x3,x4};
		tempOrientation = 0;
	}

	g->update(coords, ' ', 0, true);
	if (g->check(temp)) {
		coords = temp;
		orientation = tempOrientation;
	} else{
		g->update(coords, name, levelCreated, false);  //If it can't rotate clockwise, redraw in old place
	}

	if (isHeavy){
		down();
	}
}

void Iblock::drop() {  //Keeps calling down until it can no longer go down, then drops 
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

BlockCoord Iblock::getBlockCoord() { return coords; }

bool Iblock::getHeavy() { return isHeavy; }

char Iblock::getBlockType() { return name; }

int Iblock::lowestRowCoord() {  //Helper for hint that returns lowest row of a block
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

int Iblock::numBlocksInLowest(int row) {  //Helper for hint that returns num cells in given int row
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

//This gives a hint for the user by checking to see first, the lowest possible position the block can be in,
//and also the number of blocks in the lowest row of the lowest position. When it finds the best spot, it will
//return coordinates for them
BlockCoord Iblock::hint() {  
	int lowestRow = 20;
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
		currOrien = orientation;
		for (int i = 0; i <= 10; ++i) {  //Go through entire width
			Coord cx1 = {coords.x1.x,coords.x1.y};
			Coord cx2 = {coords.x2.x,coords.x2.y};
			Coord cx3 = {coords.x3.x,coords.x3.y};
			Coord cx4 = {coords.x4.x,coords.x4.y};
			curr = {cx1,cx2,cx3,cx4};  //Stores coordinates before dropping
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
			coords = curr;  //Return to coords before dropping and move right
			right();
			g->update(coords, ' ', 0, true);
		}
		for (int i = 10; i >= 0; --i) {  //Go through entire width
			Coord cx1 = {coords.x1.x,coords.x1.y};
			Coord cx2 = {coords.x2.x,coords.x2.y};
			Coord cx3 = {coords.x3.x,coords.x3.y};
			Coord cx4 = {coords.x4.x,coords.x4.y};
			curr = {cx1,cx2,cx3,cx4};  //Stores coordinates before dropping
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
			coords = curr;  //Return to coords before dropping and move left
			left();
			g->update(coords, ' ', 0, true);
		}				
		clockwise();
		if (orientation == currOrien) counterclockwise();
		g->update(coords, ' ', 0, true);
	}
	orientation = startOrien;
	coords = start;
	g->update(coords, name, levelCreated, false);  //Goes back to original start position and updates
	return best;
}