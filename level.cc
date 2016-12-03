#include "level.h"
#include <cstdlib>
#include <vector>
#include <ctime>

Level::Level(int n): dif{n}{ g = new Grid(dif); } // Constructor for Level 1 -4

Level::Level(int n, std::string &file): dif{n}, file{file}{ 
	f.open(file);
	g = new Grid(dif); 
} // Constructor for Level 0

Level::~Level(){ delete g; }

void Level::levelUp(){ dif++; }

void Level::levelDown(){ dif--; }


void Level::readInFile(){ // This is to be called when a Level 0 object is made in the controller
	std::string s;
	while (f >> s){
		seqInput.push_back(s);
		s.clear();
	}
} // Call it in the form Level* level = new Level(0, f); Followed by level->readInFile(); followed by level->makeblock()

int Level::getDif() const {
	return dif;
}

Block *Level::diff0Block(){
	if (count >= seqInput.size()) { throw "outofbounds"; }
	if ( seqInput[count] == "I") { count++; return new Iblock(false, g, 0); }
	else if (seqInput[count] == "J") { count++; return new Jblock(false, g, 0); }
	else if (seqInput[count] == "O") { count++; return new Oblock(false, g, 0); }
	else if (seqInput[count] == "S") { count++; return new Sblock(false, g, 0); }
	else if (seqInput[count] == "Z") { count++; return new Zblock(false, g, 0); }
	else if (seqInput[count] == "T") { count++; return new Tblock(false, g, 0); }
	else if (seqInput[count] == "Z") { count++; return new Zblock(false, g, 0); }
}

Block *Level::diff1Block(){
	int y = rand() % 12;
	if (y == 0 || y == 1){ return new Iblock(false, g, 1); }
	else if (y == 2 || y == 3){ return new Jblock(false, g, 1); }
	else if (y == 4 || y == 5){ return new Lblock(false, g, 1); }
	else if (y == 6 || y == 7){ return new Oblock(false, g, 1); }
	else if (y == 8 || y == 9){ return new Tblock(false, g, 1); }
	else if (y == 10){ return new Sblock(false, g, 1); }
	else { return new Zblock(false, g, 1); }
	
}

Block *Level::diff2Block(){
	int y = rand() % 7;
	if (y == 0){ return new Iblock(false, g, 2); }
	else if (y == 1) { return new Jblock(false, g, 2); }
	else if (y == 2) { return new Lblock(false, g, 2); }
	else if (y == 3) { return new Oblock(false, g, 2); }
	else if (y == 4) { return new Tblock(false, g, 2); }
	else if (y == 5) { return new Sblock(false, g, 2); }
	else { return new Zblock(false, g, 2); }
}

Block *Level::diff3Block(){
	int y = rand() % 9;
	if (y == 0){ return new Iblock(true, g, 3); }
	else if (y == 1){ return new Jblock(true, g, 3); }
	else if (y == 2){ return new Lblock(true, g, 3); }
	else if (y == 3){ return new Oblock(true, g, 3); }
	else if (y == 4){ return new Tblock(true, g, 3); }
	else if (y == 5 || y == 6){ return new Sblock(true, g, 3); }
	else { return new Zblock(true, g, 3); }
}

Block *Level::diff4Block(){
	return diff3Block();
} // Same as diff3block except draws the *block. 
 
Block *Level::makeBlock(){
	srand(time(NULL));
	g->addToCount();
	if (dif == 0){ return diff0Block(); }
	else if (dif == 1){ return diff1Block(); }
	else if (dif == 2){ return diff2Block(); }
	else if (dif == 3){ return diff3Block(); }
	else if (dif == 4){ return diff4Block(); }
}

/*Block *Level::I(){
	if (dif >= 3){ return new Iblock(true, g); }
	else { return new Iblock(false, g); }
}

Block *Level::J(){
	if (dif >= 3){ return new Jblock(true, g); }
	else { return new Jblock(false, g); }
}*/

Grid * Level::getGrid(){ return g; }

int Level::count = 0;
