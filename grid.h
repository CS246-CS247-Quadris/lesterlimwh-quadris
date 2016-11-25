#include <iostream>
#include <vector>
#include "blockcoord.h"
class Grid{
	int height,width;
	std::vector<vector <BlockCell> > display;
public:
	Grid(int height = 18, int width = 11);
	~Grid();
	void update(BlockCoord &b);
	bool check(BlockCoord &b);
	void RowClear();
	void hint();
	void restart();
};