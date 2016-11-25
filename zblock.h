#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include "grid.h"
#include "block.h"
#include "blockCoord.h"

class Zblock{ 
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	const char name = 'Z';

public:
	Zblock(bool isHeavy, Grid *g);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
};

#endif
