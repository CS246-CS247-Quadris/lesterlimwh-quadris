#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include "grid.h"
#include "block.h"
#include "blockCoord.h"

class Lblock{ 
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	const char name = 'L';

public:
	Lblock(bool isHeavy, Grid *g);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
};

#endif
