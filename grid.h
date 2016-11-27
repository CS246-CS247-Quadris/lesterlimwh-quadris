#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "blockcoord.h"
#include "blockcell.h"

class Grid{
	int height,width;
	int blockNum;
	std::vector<std::vector <BlockCell>> display;

public:
	Grid(int height = 18, int width = 11);
	~Grid();
	void update(const BlockCoord &b, const char c);
	bool check(const BlockCoord &b);
	std::vector<int> rowHelper(const BlockCoord &b);
	void rowClear(const BlockCoord &b);
	void hint();
	void restart();
	void addToCount(); // Called when Drop is Called
	friend std::ostream &operator<<(std::ostream &out, const Grid *g);
};

#endif