#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "blockcoord.h"
//Abstract class for all Blocks on the grid
class Block {
public:
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void down() = 0;
	virtual void counterclockwise() = 0;
	virtual void clockwise() = 0;
	virtual void drop() = 0;
	virtual char getBlockType() = 0;
	virtual bool getHeavy() = 0;
	virtual BlockCoord getBlockCoord() = 0;
	virtual BlockCoord hint() = 0;
	virtual ~Block() = default;
};

#endif
