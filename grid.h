#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "blockcoord.h"
#include "blockcell.h"

class Level;

// Interface for Grid Class
class Grid{
	int height,width; // The width and the height of the grid
	int blockNum; 
	int dif; 
	char blockLetter;
	int score = 0; // This stores the score of the game
	bool isScoreDif = true; // This a
	int lvl4Count = 0;
	std::vector<int> deletedBlocks; // This is used to calculate score
	std::vector<BlockCell> scoreRowCheck; // This is used to calculate score
	std::vector<std::vector <BlockCell>> display; // This is the main display vector for the grid

public:
	Grid(int dif, int height = 18, int width = 11);
	~Grid();
	void update(const BlockCoord &b, const char c, int level, bool empty);
	bool check(const BlockCoord &b);
	bool gameOver(const BlockCoord &b);
	std::vector<int> rowHelper(const BlockCoord &b);
	std::vector<int> rowClear(const BlockCoord &b);
	void setLetter(const char letter);
	void restart();
	void addToCount();
	void addTolvl4Count();
	void addToScore();
	bool scoreHelper(int n);
	int getScore() const;
	void clearHint();
	void dropStarBlock();
	void removeBlock(BlockCoord &b, int level);
	std::string nextBlock() const; // Called when Drop is Called
	friend std::ostream &operator<<(std::ostream &out, const Grid *g);
	friend class Graphics;
};

#endif