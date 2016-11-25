#include "level.h"
#include <cstdlib>
#include <vector>
Level::Level(int n): dif{n}{ g = new Grid(n); } // Constructor for Level 1 -4

Level::Level(int n, ifstream &f): dif{n}, f{f}{ g = new Grid(n); } // Constructor for Level 0

Level::~Level(){ delete g; }

void Level::levelUp(){ dif++; }

void Level::levelDown(){ dif--; }

void Level::readInFile(){ // This is to be called when a Level 0 object is made in the controller
	string s;
	 while (f >> s){
	 	seqInput.push_back(s);
	 	s.clear();
	 }
} // Call it in the form Level* level = new Level(0, f); Followed by level->readInFile(); followed by level->makeBlock()

Block *Level::diff0Block(){
	 if ( seqInput[count] == "I") { return new IBlock(false, g); }
	 else if (seqInput[count] == "J") { return new JBlock(false, g); }
	 else if (seqInput[count] == "O") { return new OBlock(false, g); }
	 else if (seqInput[count] == "S") { return new SBlock(false, g); }
	 else if (seqInput[count] == "Z") { return new ZBlock(false, g); }
	 else if (seqInput[count] == "T") { return new TBlock(false, g); }
	 else if (seqInput[count] == "Z") { return new ZBlock(false, g); }
	 count++;
}

Block *Level::diff1Block(){
	 int y = rand() % 12;
	 if (y == 0 || y == 1){ return new IBlock(false, g); }
	 else if (y == 2 || y == 3){ return new JBlock(false, g); }
	 else if (y == 4 || y == 5){ return new LBlock(false, g); }
	 else if (y == 6 || y == 7){ return new OBlock(false, g); }
	 else if (y == 8 || y == 9){ return new TBlock(false, g); }
	 else if (y == 10){ return new SBlock(false, g); }
	 else { return new ZBlock(false, g); }
}

Block *Level::diff2Block(){
	 int y = rand() % 7;
	 if (y == 0){ return new IBlock(false, g); }
	 else if (y == 1) { return new JBlock(false, g); }
	 else if (y == 2) { return new LBlock(false, g); }
	 else if (y == 3) { return new OBlock(false, g); }
	 else if (y == 4) { return new TBlock(false, g); }
	 else if (y == 5) { return new SBlock(false, g); }
	 else { return new ZBlock(false, g); }
}

Block *Level::diff3Block(){
	 int y = rand() % 9;
	 if (y == 0){ return new IBlock(true, g); }
	 else if (y == 1){ return new JBlock(true, g); }
	 else if (y == 2){ return new LBlock(true, g); }
	 else if (y == 3){ return new OBlock(true, g); }
	 else if (y == 4){ return new TBlock(true, g); }
	 else if (y == 5 || y == 6){ return new SBlock(true, g); }
	 else { return new ZBlock(true, g); }
	}

Block *Level::diff4Block(){
 return diff3Block();
} // Same as diff3Block except draws the *Block. 
 
Block* Level::makeBlock(){
 srand(2); // THIS IS PART OF THE COMMAND LINE ARGUMENTS. THIS WILL BE CHANGED
 if (dif == 0){ return diff0Block(); }
 else if (dif == 1){ return diff1Block(); }
 else if (dif == 2){ return diff2Block(); }
 else if (dif == 3){ return diff3Block(); }
 else if (dif == 4){ return diff4Block(); }
}

Block* Level::I(){
	if (dif >= 3){ return new IBlock(true, g); }
	else { return new IBlock(false, g); }
}

Block* Level::J(){
	if (dif >= 3){ return new JBlock(true, g); }
	else { return new JBlock(false, g); }
}