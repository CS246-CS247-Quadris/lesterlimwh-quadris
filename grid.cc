#include "grid.h"
#include <vector>
#include <iostream>
#include <map>
using namespace std;

Grid::Grid(int height, int width): height{height}, width{width}, blockNum{0},
                                   display{std::vector<std::vector<BlockCell> >(height, std::vector<BlockCell>(width, {blockNum, ' '}))}{}

Grid::~Grid(){}

void Grid::addToCount(){ ++blockNum; } // WHEN DROP IS CALLED, AFTER UPDATE IS CALLED, CALL THIS FUNCTION TO INCREASE COUNT

void Grid::update(const BlockCoord &b, const char c){
	// CAN BE CHANGED IF WE WANT TO IMPLEMENT BLOCKS OF DIFFERENT SIZES
    display[b.x1.y][b.x1.x] = {blockNum, c};
    display[b.x2.y][b.x2.x] = {blockNum, c};
    display[b.x3.y][b.x3.x] = {blockNum, c};
    display[b.x4.y][b.x4.x] = {blockNum, c};
}

bool Grid::check(const BlockCoord &b){
	if (b.x1.x < 0 || b.x2.x < 0 || b.x3.x < 0 || b.x4.x < 0) { return false; }
	if (b.x1.y < 0 || b.x2.y < 0 || b.x3.y < 0 || b.x4.y < 0) { return false; }
	if (b.x1.x >= width || b.x2.x >= width || b.x3.x >= width || b.x4.x >= width){ return false; }
	if (b.x1.y >= height || b.x2.y >= height || b.x3.y >= height || b.x4.y >= height){ return false; }
	if (display[b.x1.y][b.x1.x].letter != ' '){ return false; }
	if (display[b.x2.y][b.x2.x].letter != ' '){ return false; }
	if (display[b.x3.y][b.x3.x].letter != ' '){ return false; }
	if (display[b.x4.y][b.x4.x].letter != ' '){ return false; }
	return true;
}

void Grid::rowHelper(int &row1, int &row2, int &row3, int &row4, const BlockCoord &b){
	// Use Vector to  store the rows of each coordinate and sort from smallest to greatest

}

void Grid::rowClear(const BlockCoord &b){
	int isFull;
	int row1 = -1;
	int row2 = -1;
	int row3 = -1;
	int row4 = -1;
	if (b.x1.y > b.x2.y && b.x2.y > b.x3.y && b.x3.y > b.x4.y){
		row1 = b.x1.y;
		row2 = b.x2.y;
		row3 = b.x3.y;
		row4 = b.x4.y;
	}
	else if (b.x4.y > b.x3.y && b.x3.y > b.x2.y && b.x2.y > b.x1.y){
		row1 = b.x4.y;
	}

	for (int i = 0; i < height; ++i){
		isFull = 1;
		for(int j = 0; j < width; ++j){
			if (display[i][j].letter == ' '){ 
				isFull = 0;
				break; 
			}
		}
	}
}

void Grid::restart(){}
void Grid::hint(){}
std::ostream &operator<<(std::ostream &out , const Grid *g){
        for (int i = 0; i < g->width; ++i){
         out << '_';
        }
        out << endl;
	for (int i = 0; i < g->height; ++i){
		for (int j = 0; j < g->width; ++j){
			out << g->display[i][j].letter << " ";
		}
		out << endl;
	}
        for (int i = 0; i < g->width; ++i){
         out << '_';
        }
	return out;
}
