#include <iostream>
#include <string>
#include "level.h"
using namespace std;

int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;

  try {
    cout << "Please enter a level: ";
    int n; 
    cin >> n;
    cout << endl;
    Level lvl{n}; // create a new level with dif = n (this initialize a grid too)

    while (true) { // change true to !isGameOver later
      Block * b = lvl.makeBlock(); // generate a random block depending on level and store it in a Block pointer
      const char blockType = b->getBlockType();
      BlockCoord coords = b->getBlockCoord();
      lvl.g->update(coords, blockType); // update the grid to see the new block
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
      } else if (cmd == "clockwise"){
        b->clockwise();
        lvl.g->update(coords, blockType); // update the grid to rotate the block clockwise
      } else if (cmd == "cclockwise"){
        b->counterclockwise();
        lvl.g->update(coords, blockType); // update the grid to rotate the block counter-clockwise
      }
      delete b;
    }
  }
  catch (ios::failure &) {
  }
}
