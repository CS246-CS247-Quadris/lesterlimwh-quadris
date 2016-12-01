#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include "grid.h"
#include "block.h"
#include "blockcoord.h"

class Zblock:public Block { 
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	int levelCreated; //Needed to pass down to blockcells
	const char name = 'Z';

public:
	Zblock(bool isHeavy, Grid *g, int levelCreated);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
	BlockCoord getBlockCoord() override;
	char getBlockType() override;
};

#endif
