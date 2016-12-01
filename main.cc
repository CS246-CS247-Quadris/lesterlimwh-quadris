#include <iostream>
#include <fstream>
#include <string>
#include "level.h"
#include "window.h"
#include "graphics.h"
using namespace std;

int main() {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;

  try {
    cout << "Please enter a level: ";
    int n; 
    cin >> n;
    cout << endl;
    int rows = 18; // The default grid presets of the game
    int columns = 11; // The default grid presets of the game
    char blockType;
    char nextBlockType;
    BlockCoord coords;
    bool isGameOver = false;
    Xwindow *window = new Xwindow();
    Graphics *view = new Graphics(*window, rows, columns);
    if (n == 0){ //NOTE THAT NEXT BLOCK FEATURE IS NOT WORKING FOR LEVEL 0 YET
      string file = "test.txt";
      Level lvl(n, file);
      lvl.readInFile();
      Block *b = lvl.makeBlock();
      //Block *next = lvl.makeBlock();
      blockType = b->getBlockType();
      //nextBlockType = next->getBlockType();
      lvl.g->setLetter(nextBlockType);
      coords = b->getBlockCoord();
      view->update(coords, blockType);
      lvl.g->update(coords, blockType, lvl.getDif(), false);
      cout << lvl.g << endl;
      while (!isGameOver) { // change true to !isGameOver
        cin >> cmd;
        if (cmd == "a"){
          b->left();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "d"){
          b->right();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "s"){
          b->down();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "x"){
          b->drop();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
          //lvl.g->addToCount();
          lvl.g->rowClear(coords);
          delete b;
          b = lvl.makeBlock();
          //b = next;
          //next = lvl.makeBlock();
          coords = b->getBlockCoord();
          blockType = b->getBlockType();
          //nextBlockType = next->getBlockType();
          lvl.g->setLetter(nextBlockType);
          isGameOver = lvl.g->gameOver(coords);
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType); 
        } else if (cmd == "c"){
          b->clockwise();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "z"){
          b->counterclockwise();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        }
        cout << lvl.g << endl;
      }
      delete b;
      //delete next;
    } else{
      Level lvl(n);
      Block *b = lvl.makeBlock();
      Block *next = lvl.makeBlock();
      blockType = b->getBlockType();
      nextBlockType = next->getBlockType();
      lvl.g->setLetter(nextBlockType);
      coords = b->getBlockCoord();
      lvl.g->update(coords, blockType, lvl.getDif(), false);
      view->update(coords, blockType);
      cout << lvl.g << endl;
      while (!isGameOver) {
        cin >> cmd;
        if (cmd == "a"){
          view->update(coords, ' ');
          b->left();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "d"){
          view->update(coords, ' ');
          b->right();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "s"){
          view->update(coords, ' ');
          b->down();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "x"){
          view->update(coords, ' ');
          b->drop();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
          lvl.g->rowClear(coords);
          //lvl.g->addToCount();
          delete b;
          b = next;
          next = lvl.makeBlock();
          coords = b->getBlockCoord();
          blockType = b->getBlockType();
          nextBlockType = next->getBlockType();
          lvl.g->setLetter(nextBlockType);
          isGameOver = lvl.g->gameOver(coords);
          lvl.g->update(coords, blockType, lvl.getDif(), false); 
          view->update(coords, blockType);
        } else if (cmd == "c"){
          view->update(coords, ' ');
          b->clockwise();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "z"){
          view->update(coords, ' ');
          b->counterclockwise();
          coords = b->getBlockCoord();
          lvl.g->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        }
        cout << lvl.g << endl;
      } // while !isGameOver
      delete b; 
      delete next;

    }
    delete window;
    delete view; // else
  } // try
  catch (ios::failure &) {
  }
}

// Pranav can you see this
