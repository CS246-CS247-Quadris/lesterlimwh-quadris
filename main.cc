#include <iostream>
#include <fstream>
#include <string>
#include "level.h"
using namespace std;


int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;

  // WHY IS THERE A SEG FAULT

  try {
    cout << "Please enter a level: ";
    int n; 
    cin >> n;
    cout << endl;
    string file = "test.txt";
    char blockType;
    BlockCoord coords;
    // WARNING!!! SOME COMMENTS AHEAD. RIGHT NOW, LEVEL WILL AUTOMATICALLY BE INITIALIZED WITH A FILE REGARDLESS OF
    // WHAT THE LEVEL IS. THIS WILL BE ADJUSTED AFTER SEG FAULTS ARE FIXED
     Level lvl(n, file);
     lvl.readInFile(); // READS IN FILE
    Block *b = lvl.makeBlock();
    //Level lvl{n}; // create a new level with dif = n (this initialize a grid too)

    while (true) { // change true to !isGameOver later
      //Block * b = lvl.makeBlock(); // generate a random block depending on level and store it in a Block pointer
      blockType = b->getBlockType(); // FIRST SEG FAULT HERE. CODE DOES NOT REACH PRINT STATEMENT
      coords = b->getBlockCoord();
      lvl.g->update(coords, blockType); // update the grid to see the new block
      cout << blockType << " " << coords.x1.x << " " << coords.x1.y << endl; // Just to see output
      cin >> cmd;
      if (cmd == "left"){
        b->left();
        lvl.g->update(coords, blockType); // update the grid to shift the block one unit left
      } else if (cmd == "right"){
        b->right();
        lvl.g->update(coords, blockType); // update the grid to shift the block one unit right
      } else if (cmd == "down"){
        b->down();
        lvl.g->update(coords, blockType); // update the grid to shift the block one unit down
      } else if (cmd == "drop"){
        b->drop();
        lvl.g->update(coords, blockType); // update the grid to place the block
        delete b;
        b = lvl.makeBlock();
      } else if (cmd == "clockwise"){
        b->clockwise();
        lvl.g->update(coords, blockType); // update the grid to rotate the block clockwise
      } else if (cmd == "cclockwise"){
        b->counterclockwise();
        lvl.g->update(coords, blockType); // update the grid to rotate the block counter-clockwise
      }
      cout << lvl.g;
      
    }
  }
  catch (ios::failure &) {
  }
}
