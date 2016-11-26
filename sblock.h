#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include "grid.h"
#include "block.h"
#include "blockcoord.h"

class Sblock:public Block {
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	const char name = 'S';

public:
	Sblock(bool isHeavy, Grid *g);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
	BlockCoord getBlockCoord() override;
	char getBlockType() const override;
};

#endif