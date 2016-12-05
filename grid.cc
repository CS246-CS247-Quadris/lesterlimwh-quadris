#include "grid.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//std::vector<int> deletedBlocks;

// Constructor for Grid
Grid::Grid(int dif, int height, int width): dif{dif}, height{height}, width{width}, blockNum{0},
                                   display{std::vector<std::vector<BlockCell> >(height, std::vector<BlockCell>(width, {blockNum, dif, ' '}))}{}

// Destructor for Grid
Grid::~Grid(){}

// Sets the letter of of the Grid to the provided letter
void Grid::setLetter(const char letter){
	blockLetter = letter;
}

// Returns the current score of the game
int Grid::getScore() const { return score; }

// When makeBlock is called, after update is called, call this function to increase count
void Grid::addToCount(){ ++blockNum; } 


//Used to keep track of how many blocks have been created before a row has been cleared
void Grid::addTolvl4Count(){ ++lvl4Count; }  


//Returns true if given int is within deletedBlocks vec
bool Grid::scoreHelper(int n) { 
	int len = deletedBlocks.size();
	for (int i = 0; i < len; i++) {
		if (n == i) {
			return true;
		}
	}
	return false;
}

// This adds to the current score using the requested scoring algorithm
void Grid::addToScore() {
	std::vector<int> v; // gets filled with the levels removed blocks were created in
	bool ingrid;
	for (int num = 2; num <= blockNum; num++) {
		ingrid = false;
		for (int i = height - 1; i >= 0; --i) {
			for (int j = 0; j < width; ++j) {
				if (display[i][j].count == num) { //Sets ingrid to true the block with this count is in the grid
					ingrid = true;
				}
			}
		}
		if (ingrid == false) {
			if (!scoreHelper(num)) {
				deletedBlocks.emplace_back(num);
				for (int j = 0; j < scoreRowCheck.size(); ++j) {
					if (scoreRowCheck[j].count == num) {
						v.emplace_back(scoreRowCheck[j].levelCreated); //Adds to v when current count = num
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < v.size(); i++) {
		score += (v[i]+1) * (v[i]+1); 
	}
}


// Updates the given coordinates to include the provided letter. Also sets their isChanged parameter to true so 
// the Graphics will update it
void Grid::update(const BlockCoord &b, const char c, int level, bool empty ){ //added empty to know if resetting block
	dif = level;
	if (empty) {
		display[b.x1.y][b.x1.x] = {0,level,' ', true};
	    display[b.x2.y][b.x2.x] = {0,level,' ', true};
	    display[b.x3.y][b.x3.x] = {0,level,' ', true};
	    display[b.x4.y][b.x4.x] = {0,level,' ', true};
	} else {
	    display[b.x1.y][b.x1.x] = {blockNum,level,c, true};
	    display[b.x2.y][b.x2.x] = {blockNum,level,c, true};
	    display[b.x3.y][b.x3.x] = {blockNum,level,c, true};
	    display[b.x4.y][b.x4.x] = {blockNum,level,c, true};
	}
}

// Checks the given coordinates and returns true if the block can be placed there without any conflicts
bool Grid::check(const BlockCoord &b){
	if (b.x1.x < 0 || b.x2.x < 0 || b.x3.x < 0 || b.x4.x < 0) { return false; } // First 4 lines check the extreme ends of the display
	if (b.x1.y < 0 || b.x2.y < 0 || b.x3.y < 0 || b.x4.y < 0) { return false; } 
	if (b.x1.x >= width || b.x2.x >= width || b.x3.x >= width || b.x4.x >= width){ return false; }
	if (b.x1.y >= height || b.x2.y >= height || b.x3.y >= height || b.x4.y >= height){ return false; }
	if (display[b.x1.y][b.x1.x].letter != ' '){ return false; } // These check to make sure the letters are all spaces 
	if (display[b.x2.y][b.x2.x].letter != ' '){ return false; }
	if (display[b.x3.y][b.x3.x].letter != ' '){ return false; }
	if (display[b.x4.y][b.x4.x].letter != ' '){ return false; }
	return true;
}


// This is a helper for rowClear. It returns the rows that dropped block is a part of  in reverse sorted order
vector<int> Grid::rowHelper(const BlockCoord &b){
	// Use Vector to  store the rows of each coordinate and sort from smallest to greatest
	vector<int> rows;
  	rows.emplace_back(b.x1.y);
  	rows.emplace_back(b.x2.y);
  	rows.emplace_back(b.x3.y);
  	rows.emplace_back(b.x4.y);
  	rows.erase(unique(rows.begin(), rows.end()), rows.end());
  	sort(rows.begin(), rows.end()); // Sort the vector
  	reverse(rows.begin(), rows.end()); // Reverse it. This is so the highest row is cleared first so none of the rows below are changed
  	return rows;
}

// The actual rowClear function. It clears rows that have been filled and calls the addToScore function 
vector<int> Grid::rowClear(const BlockCoord &b){
	vector<int> deleted;
	scoreRowCheck.clear();
	vector<int> rows = rowHelper(b); // Storing the array from rowHelper
	int size = rows.size();
	if (size >= 1){ isScoreDif = 1;} // If the size of the cleared rows vector is 1, then the score will be changed
	bool isFull = true;

	// Checking if the rows need to be cleared
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < width; ++j){
			if (display[rows[i]][j].letter == ' '){
				isFull = false;
				break;
			}
		}
		if (isFull){
			lvl4Count = 0;
			for (int z = 0; z < width; ++z){
				scoreRowCheck.emplace_back(display[rows[i]][z]); // If the row is full, add it to the scoreRowCheck
			}
			deleted.emplace_back(rows[i]);
			display.erase(display.begin() + rows[i]);
			// Dealing with the score
			score += (dif + 1) * (dif + 1); //Added when row is cleared
			display.push_back(vector<BlockCell>(width, {0,0,' '})); // 0 BECAUSE NO BLOCK IS ASSIGNED TO THE NEW ROW

			// This for loop takes every row above the cleared one and sets the isChanged boolean to true. 
			// This is for the graphics display
			for (int j = rows[i]; j < height; ++j){
				for (int k = 0; k < width; ++k){
					display[j][k].isChanged = true;
				}
			}
		}
		isFull = true;
	}
	addToScore();
	return deleted;
}

// This clears the hint after the user makes another manipulation to the block
void Grid::clearHint() {
	for (int i = height - 1; i >= 0; --i) {
		for (int j = 0; j < width; ++j) {
			if (display[i][j].letter == '?') {
				display[i][j] = {0,0,' '};
			}
		}
	}
}


// Drops a star block on level 4 after 5 blocks have been dropped without a row being cleared
void Grid::dropStarBlock() {//COUNT IS MESSED UP BUT IT KINDA WORKS
	int starCol = 5;
	if (lvl4Count != 0 && lvl4Count % 5 == 0) {
		for (int i = height - 1; i >= 0; --i) {
			if (i == 0 && display[i][starCol].letter == ' ') {
				display[i][starCol].letter = '*';
				display[i][starCol].isChanged = true;
			} else if (i != 0 && display[i-1][starCol].letter != ' ') {
				display[i][starCol].letter = '*';
				display[i][starCol].isChanged = true;
				break;
			}
		}
	}
}

// Removes a block from the display by updating its BlockCell
void Grid::removeBlock(BlockCoord &b, int level){
	display[b.x1.y][b.x1.x] = {0,level,' '};
    display[b.x2.y][b.x2.x] = {0,level,' '};
    display[b.x3.y][b.x3.x] = {0,level,' '};
    display[b.x4.y][b.x4.x] = {0,level,' '};
}


// Checks if the player has reached the top of the screen
bool Grid::gameOver(const BlockCoord &b){
	return !(check(b));
}

// Displays the nextBlock on the textdisplay by appending to a string depending
// on the blockLetter
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

// Restarts the game by resetting the score and clearing the grid
void Grid::restart(){
	for (int i = height - 1; i >= 0; --i) {
		for (int j = 0; j < width; ++j) {
			display[i][j] = {0,0,' '};
		}
	}
	blockNum = 0;
	score = 0;
	lvl4Count = 0;
	deletedBlocks.clear();
	scoreRowCheck.clear();
}

// Outputs the grid
std::ostream &operator<<(std::ostream &out , const Grid *g){
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
    out << endl << "Next Block:" << endl;
    out << g->nextBlock();
	return out;
}

