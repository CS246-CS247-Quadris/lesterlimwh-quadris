#include "grid.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

std::vector<int> deletedBlocks;

Grid::Grid(int dif, int height, int width): dif{dif}, height{height}, width{width}, blockNum{0},
                                   display{std::vector<std::vector<BlockCell> >(height, std::vector<BlockCell>(width, {blockNum, dif, ' '}))}{}

Grid::~Grid(){}

void Grid::setLetter(const char letter){
	blockLetter = letter;
}

int Grid::getScore() const { return score; }

void Grid::addToCount(){ ++blockNum; } // WHEN DROP IS CALLED, AFTER UPDATE IS CALLED, CALL THIS FUNCTION TO INCREASE COUNT

bool Grid::scoreHelper(int n) { //Returns true if given int is within deletedBlocks vec
	int len = deletedBlocks.size();
	for (int i = 0; i < len; i++) {
		if (n == i) {
			return true;
		}
	}
	return false;
}

void Grid::addToScore() {
	std::vector<int> v; // gets filled with the levels removed blocks were created in
	bool ingrid;
	for (int num = 2; num <= blockNum; num++) {
		ingrid = false;
		for (int i = height - 1; i >= 0; --i) {
			for (int j = 0; j < width; ++j) {
				if (display[i][j].count == num) {
					ingrid = true;
				}
			}
		}
		if (ingrid == false) {
			if (!scoreHelper(num)) {
				deletedBlocks.emplace_back(num);
				for (int j = 0; j < scoreRowCheck.size(); ++j) {
					if (scoreRowCheck[j].count == num) {
						v.emplace_back(scoreRowCheck[j].levelCreated);
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < v.size(); i++) {
		score += (v[i]+1) * (v[i]+1);
	}
	cout << "LEN OF ARRAY IS: " << v.size() <<endl;
}

void Grid::update(const BlockCoord &b, const char c, int level, bool empty ){ //added empty to know if resetting block
	// CAN BE CHANGED IF WE WANT TO IMPLEMENT BLOCKS OF DIFFERENT SIZES
	if (empty) {
		display[b.x1.y][b.x1.x] = {0,level,' '};
	    display[b.x2.y][b.x2.x] = {0,level,' '};
	    display[b.x3.y][b.x3.x] = {0,level,' '};
	    display[b.x4.y][b.x4.x] = {0,level,' '};
	} else {
	    display[b.x1.y][b.x1.x] = {blockNum,level,c};
	    display[b.x2.y][b.x2.x] = {blockNum,level,c};
	    display[b.x3.y][b.x3.x] = {blockNum,level,c};
	    display[b.x4.y][b.x4.x] = {blockNum,level,c};
	}
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

vector<int> Grid::rowClear(const BlockCoord &b){
	vector<int> deleted;
	scoreRowCheck.clear();
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
			for (int z = 0; z < width; ++z){
				scoreRowCheck.emplace_back(display[rows[i]][z]);
			}
			deleted.emplace_back(rows[i]);
			display.erase(display.begin() + rows[i]);
			// ADD SCORE HERE
			score += (dif + 1) * (dif + 1); //Added when row is cleared
			display.push_back(vector<BlockCell>(width, {0,0,' '})); // 0 BECAUSE NO BLOCK IS ASSIGNED TO THE NEW ROW
			//for (int k = i; k < size; ++k){ // REDUCES THE VALUE OF EACH ROW IN ROWS SO THAT WE DON'T CHECK THE ROW ABOVE THE ONE WE WANT
			//	rows[k] = rows[k] - 1;
			//}
			//addToScore();
		}
		isFull = true;
	}
	addToScore();
	return deleted;
}
bool Grid::gameOver(const BlockCoord &b){
	return !(check(b));
}

string Grid::nextBlock() const{
	string s;
	if (blockLetter == 'I'){
		s = "IIII";
	}
	else if (blockLetter== 'J'){
		s= "J";
		s.append("\n");
		s.append("JJJ");
	}
	else if (blockLetter == 'L'){
		s = "  L";
		s.append("\n");
		s.append("LLL");
	}
	else if (blockLetter == 'O'){
		s = "OO";
		s.append("\n");
		s.append("OO");
	}
	else if (blockLetter == 'S'){
		s = " SS";
		s.append("\n");
		s.append("SS ");
	}
	else if (blockLetter == 'Z'){
		s = "ZZ ";
		s.append("\n");
		s.append(" ZZ");
	}
	else {
		s = "TTT";
		s.append("\n");
		s.append(" T ");
	}
	return s;
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
	out << "Level: " << g->dif << endl;
	out << "Score: " << g->score << endl;
	out << "High Score" << g->score << endl;
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
    //out << endl << "Next Block:" << endl;
    //out << g->nextBlock();
	return out;
}

// Pranav can you see this

