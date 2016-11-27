#include "grid.h"
#include <vector>
#include <iostream>
#include <algorithm>
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

vector<int> Grid::rowHelper(/*int &row1, int &row2, int &row3, int &row4,*/ const BlockCoord &b){
	// Use Vector to  store the rows of each coordinate and sort from smallest to greatest
	vector<int> rows;
	 //THIS CAN BE CHANGED IF WE DECIDE TO ALLOW FOR BLOCKS OF DIFF SIZE
  	rows.emplace_back(b.x1.y);
  	rows.emplace_back(b.x2.y);
  	rows.emplace_back(b.x3.y);
  	rows.emplace_back(b.x4.y);
  	rows.erase(unique(rows.begin(), rows.end()), rows.end());
  	return rows;
}

void Grid::rowClear(const BlockCoord &b){
	vector<int> rows = rowHelper(b);
	int size = rows.size();
	bool isFull = true;
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < width; ++j){
			if (display[rows[i]][j].letter == ' '){
				isFull = false;
				break;
			}
		}
		if (isFull){
			display.erase(display.begin() + rows[i]);
			// ADD SCORE HERE
			display.push_back(vector<BlockCell>(width, {0, ' '})); // 0 BECAUSE NO BLOCK IS ASSIGNED TO THE NEW ROW
			for (int k = i; k < size; ++k){ // REDUCES THE VALUE OF EACH ROW IN ROWS SO THAT WE DON'T CHECK THE ROW ABOVE THE ONE WE WANT
				rows[k] = rows[k] - 1;
			}
		}
	}
}


void Grid::restart(){}
void Grid::hint(){}
std::ostream &operator<<(std::ostream &out , const Grid *g){
    /*    for (int i = 0; i < g->width; ++i){
         out << '_';
        }
        out << endl;
		for (int i = 0; i < g->height; ++i){
		for (int j = 0; j < g->width; ++j){
			out << g->display[i][j].letter << " "; // MAY ADD IF STATEMENTS TO REMOVE " " FOR LAST ENTRY IN ROW
			}
		out << endl;
		}
        for (int i = 0; i < g->width; ++i){
         	out << '_';
        }
	return out;
	*/
	for (int i = g->width - 1; i >= 0; --i){
		out << "--";
	}
	out << endl;
	for (int i = g->height - 1; i >= 0; --i){
		for (int j = 0; j < g->width; ++j){
			out << g->display[i][j].letter << " "; // MAY ADD IF STATEMENTS TO REMOVE " " FOR LAST ENTRY IN ROW
			}
		out << endl;
		}
        for (int i = g->width - 1; i >= 0; --i){
         	out << "--";
        }
	return out;
}
