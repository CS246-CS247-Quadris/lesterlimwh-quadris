#include <iostream>
#include <fstream>
#include "blockcoord.h"
class Block;

class Level{
 int dif;
 Grid *g;
 BlockCoord *b;
 ifstream f;
 Block* diff0Block();
 Block* diff1Block();
 Block* diff2Block();
 Block* diff3Block();
 Block* diff4Block();
 public:
  Level(int n);
  ~Level();
  void levelUp();
  void levelDown();
  Block* makeBlock();
}; 
