#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "blockcoord.h"
#include "blockcell.h"

class Level;
class Grid{
	int height,width;
	int blockNum;
	int dif; 
	char blockLetter;
	int score = 0;
	bool isScoreDif = true;
	int lvl4Count = 0;
	std::vector<int> deletedBlocks;
	std::vector<BlockCell> scoreRowCheck;
	std::vector<std::vector <BlockCell>> display;

public:
	Grid(int dif, int height = 18, int width = 11);
	~Grid();
	void update(const BlockCoord &b, const char c, int level, bool empty);
	bool check(const BlockCoord &b);
	bool gameOver(const BlockCoord &b);
	std::vector<int> rowHelper(const BlockCoord &b);
	std::vector<int> rowClear(const BlockCoord &b);
	void setLetter(const char letter);
	void hint();
	void restart();
	void addToCount();
	void addTolvl4Count();
	void resetlvl4Count();
	void addToScore();
	bool scoreHelper(int n);
	int getScore() const;
	void dropStarBlock();
	void removeBlock(BlockCoord &b, int level);
	std::string nextBlock() const; // Called when Drop is Called
	friend std::ostream &operator<<(std::ostream &out, const Grid *g);
	friend class Graphics;
};

#endif