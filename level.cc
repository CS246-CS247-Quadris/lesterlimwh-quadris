#include "level.h"
#include <cstdlib>
Level::Level(int n): dif{n}{
 g = new Grid(/* Whatever PARAMETRS IT HAS*/);
}
Level::~Level(){}
void Level::levelUp(){ dif++; }
void Level::levelDown(){ dif--; }
Block *Level::diff1Block(){
 //srand(2); // THIS IS PART OF THE COMMAND LINE ARGUMENTS. THIS WILL BE CHANGED
 int y = rand() % 12;
 if (y == 0 || y == 1){
  return new IBlock(b, false, g);
 }
 else if (y == 2 || y == 3){ 
  return new JBlock(b, false, g);
 }
 else if (y == 4 || y == 5){
  return new LBlock(b, false, g);
 }
 else if (y == 6 || y == 7){
  return new OBlock(b, false, g);
 }
 else if (y == 8 || y == 9){
  return new TBlock(b, false, g);
 }
 else if (y == 10){
  return new SBlock(b, false, g);
 }
 else {
  return new ZBlock(b, false, g);
 }
}

Block *Level::diff2Block(){
 int y = rand() % 7;
 if (y == 0){ return new IBlock(BlockCoord b, false, g); }
 else if (y == 1) { return new JBlock(b, false, g); }
 else if (y == 2) { return new LBlock(b, false, g); }
 else if (y == 3) { return new OBlock(b, false, g); }
 else if (y == 4) { return new TBlock(b, false, g); }
 else if (y == 5) { return new SBlock( b, false, g); }
 else { return new ZBlock(BlockCoord b, false, g); }
}

Block *Level::diff3Block(){
 int y = rand() % 9;
 if (y == 0){ return new IBlock( b, true, g); }
 else if (y == 1){ return new JBlock( b, true, g); }
 else if (y == 2){ return new LBlock( b, true, g); }
 else if (y == 3){ return new OBlock( b, true, g); }
 else if (y == 4){ return new TBlock( b, true, g); }
 else if (y == 5 || y == 6){ return new SBlock( b, true, g); }
 else { return new ZBlock( b, true, g); }
}

Block *Level::diff4Block(){} // Same as diff3Block except draws the *Block. 
 
Block* Level::makeBlock(){
 srand(2); // THIS IS PART OF THE COMMAND LINE ARGUMENTS. THIS WILL BE CHANGED
 if (dif == 0){ return diff0Block(); }
 else if (dif == 1){ return diff1Block(); }
 else if (dif == 2){ return diff2Block(); }
 else if (dif == 3){ return diff3Block(); }
 else if (dif == 4){ return diff4Block(); }
}
