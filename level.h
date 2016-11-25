#include <iostream>
#include <fstream>
#include "blockcoord.h"
#include <vector>
class Block;

class Level{
 static int count = 0;
 int dif;
 Grid *g;
 ifstream f;
 std::vector<string> seqInput;
 Block* diff0Block();
 Block* diff1Block();
 Block* diff2Block();
 Block* diff3Block();
 Block* diff4Block();
 public:
  Level(int n);
  Level(int n, ifstream &f);
  ~Level();
  void readInFile();
  void levelUp();
  void levelDown();
  Block* makeBlock();
}; 
