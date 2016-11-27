#include <iostream>
#include <fstream>
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
    char blockType;
    BlockCoord coords;

    if (n == 0){
      string file = "test.txt";
      Level lvl(n, file);
      lvl.readInFile();
      Block *b = lvl.makeBlock();

      while (true) { // change true to !isGameOver later
        blockType = b->getBlockType();
        coords = b->getBlockCoord();
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
    } else{
      Level lvl(n);
      Block *b = lvl.makeBlock();
      blockType = b->getBlockType();
      coords = b->getBlockCoord();
      lvl.g->update(coords, blockType);
      cout << lvl.g << endl;

      while (true) { // change true to !isGameOver
        cin >> cmd;
        if (cmd == "a"){
          b->left();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType);
        } else if (cmd == "d"){
          b->right();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType);
        } else if (cmd == "s"){
          b->down();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType);
        } else if (cmd == "x"){
          b->drop();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType);
          delete b;
          b = lvl.makeBlock();
          coords = b->getBlockCoord();
          blockType = b->getBlockType();
          lvl.g->update(coords, blockType); 
        } else if (cmd == "c"){
          b->clockwise();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType);
        } else if (cmd == "z"){
          b->counterclockwise();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType);
        }
        cout << lvl.g << endl;
      } // while !isGameOver
    } // else
  } // try
  catch (ios::failure &) {
  }
}
