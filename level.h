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

// Interface for Level Class
class Level{
	static int count = 0; // Count to keep track of reading through files
	int dif;
	int fileSize;
	Grid *g; // Pointer to grid. Initialized in constructor
	std::ifstream f;
	std::string file;
	std::vector<std::string> seqInput;
	Block *diff0Block(); 
	Block *diff1Block();
	Block *diff2Block();
	Block *diff3Block();
	Block *diff4Block();
	public:
	Level(int n);
	Level(int n, std::string &file);
	~Level();
	void readInFile();
	void readRandomFile(std::string randomFile);
	void levelUp();
	void levelDown();
	int getDif() const;
	Block *makeBlock(bool norandom = false);
	Grid * getGrid();
	Block *iBlock();
	Block *jBlock();
	Block *lBlock();
	Block *oBlock();
	Block *sBlock();
	Block *zBlock();
	Block *tBlock();
}; 
