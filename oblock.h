#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "grid.h"
#include "block.h"
#include "blockcoord.h"
//Interface for Oblock
class Oblock:public Block { 
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	int levelCreated; //Needed to pass down to blockcells
	const char name = 'O';

public:
	Oblock(bool isHeavy, Grid *g, int levelCreated);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
	BlockCoord getBlockCoord() override;
	bool getHeavy() override;
	char getBlockType() override;
	int lowestRowCoord();
	int numBlocksInLowest(int row);
	BlockCoord hint() override;
};

#endif
