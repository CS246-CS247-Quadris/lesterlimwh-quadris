#include "level.h"
#include <cstdlib>
#include <vector>
#include <ctime>

Level::Level(int n): dif{n}{ g = new Grid(dif); }

Level::Level(int n, std::string &file): dif{n}, file{file}{ 
	f.open(file);
	g = new Grid(dif); 
}

Level::~Level(){ delete g; }

void Level::levelUp(){
	int maxLvl = 4;
	if (dif < maxLvl) dif++; 
}

void Level::levelDown(){ 
	int minLvl = 0;
	if (dif > minLvl) dif--; 
}


void Level::readInFile(){
	std::string s;
	while (f >> s){
		seqInput.push_back(s);
		s.clear();
	}
} // Call it in the form Level* level = new Level(0, f); Followed by level->readInFile(); followed by level->makeblock()

void Level::readRandomFile(std::string randomFile){
	std::string s;
	f.open(randomFile);
	while (f >> s){
		seqInput.push_back(s);
		s.clear();
	}
}

int Level::getDif() const {
	return dif;
}

Block *Level::diff0Block(){
	if (count >= seqInput.size()) { throw "outofbounds" ; }
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
	g->dropStarBlock();
	int y = rand() % 9;
	if (y == 0){ return new Iblock(true, g, 4); }
	else if (y == 1){ return new Jblock(true, g, 4); }
	else if (y == 2){ return new Lblock(true, g, 4); }
	else if (y == 4){ return new Oblock(true, g, 4); }
	else if (y == 4){ return new Tblock(true, g, 4); }
	else if (y == 5 || y == 6){ return new Sblock(true, g, 4); }
	else { return new Zblock(true, g, 4); }
}
 
Block *Level::makeBlock(bool norandom){
	srand(time(NULL));
	g->addToCount();
	if (norandom){ return diff0Block(); }
	else if (dif == 0){ return diff0Block(); }
	else if (dif == 1){ return diff1Block(); }
	else if (dif == 2){ return diff2Block(); }
	else if (dif == 3){ return diff3Block(); }
	else if (dif == 4){ return diff4Block(); }
}

Grid * Level::getGrid(){ return g; }

int Level::count = 0;

Block *Level::iBlock(){
	return new Iblock(false, g, dif);
}

Block *Level::jBlock(){
	return new Jblock(false, g, dif);
}

Block *Level::lBlock(){
	return new Lblock(false, g, dif);
}

Block *Level::oBlock(){
	return new Oblock(false, g, dif);
}

Block *Level::sBlock(){
	return new Sblock(false, g, dif);
}

Block *Level::zBlock(){
	return new Zblock(false, g, dif);
}

Block *Level::tBlock(){
	return new Tblock(false, g, dif);
}
