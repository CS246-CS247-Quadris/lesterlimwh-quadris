#include <iostream>
#include <fstream>
#include "grid.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#include <vector>

class Block;

class Level{
	static int count;
	int dif;
	//Grid *g;
	std::ifstream f;
        std::string file;
	std::vector<std::string> seqInput;
	Block *diff0Block();
	Block *diff1Block();
	Block *diff2Block();
	Block *diff3Block();
	Block *diff4Block();
	public:
	Grid *g; // temporarily make g public for main to access (remove after controller has been created)	
	Level(int n);
	Level(int n, std::string &file);
	~Level();
	void readInFile();
	void levelUp();
	void levelDown();
	Block *makeBlock();
}; 
