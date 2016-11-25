#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include "grid.h"
#include "block.h"
#include "blockCoord.h"

class Jblock{ 
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	const char name = 'J';

public:
	Jblock(bool isHeavy, Grid *g);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
};

#endif
