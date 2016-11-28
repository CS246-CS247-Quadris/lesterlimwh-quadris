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
    bool isGameOver = false;

    if (n == 0){
      string file = "test.txt";
      Level lvl(n, file);
      lvl.readInFile();
      Block *b = lvl.makeBlock();
      cout << lvl.g << endl;
      while (!isGameOver) { // change true to !isGameOver
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
          isGameOver = lvl.g->gameOver(coords);
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
      }
      if (b){ delete b; }
    } else{
      Level lvl(n);
      Block *b = lvl.makeBlock();
      blockType = b->getBlockType();
      coords = b->getBlockCoord();
      lvl.g->update(coords, blockType);
      cout << lvl.g << endl;

      while (!isGameOver) { // change true to !isGameOver
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
          isGameOver = lvl.g->gameOver(coords);
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
      }
      delete b; // while !isGameOver
    }
    // else
  } // try
  catch (ios::failure &) {
  }
}
