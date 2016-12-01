#include <iostream>
#include "controller.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
  cout << "Please enter a level: ";
  int n;
  cin >> n;
  cout << endl;
  if (n == 0){
    Controller ctrl(n, "test.txt"); // change test.txt to sequence.txt when done testing
    ctrl.startGame();
  } else{
    Controller ctrl(n);
    ctrl.startGame();
  }

  /*cin.exceptions(ios::eofbit|ios::failbit);
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
      lvl.getGrid()->setLetter(nextBlockType);
      coords = b->getBlockCoord();
      view->update(coords, blockType);
      lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
      cout << lvl.getGrid() << endl;
      while (!isGameOver) { // change true to !isGameOver
        cin >> cmd;
        if (cmd == "a"){
          b->left();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
        } else if (cmd == "d"){
          b->right();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "s"){
          b->down();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "x"){
          b->drop();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
          //lvl.getGrid()->addToCount();
          lvl.getGrid()->rowClear(coords);
          delete b;
          b = lvl.makeBlock();
          //b = next;
          //next = lvl.makeBlock();
          coords = b->getBlockCoord();
          blockType = b->getBlockType();
          //nextBlockType = next->getBlockType();
          lvl.getGrid()->setLetter(nextBlockType);
          isGameOver = lvl.getGrid()->gameOver(coords);
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
          view->update(coords, blockType); 
        } else if (cmd == "c"){
          b->clockwise();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType); 
        } else if (cmd == "z"){
          b->counterclockwise();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        }
        cout << lvl.getGrid() << endl;
      }
      delete b;
      //delete next;
    } else{
      Level lvl(n);
      Block *b = lvl.makeBlock();
      Block *next = lvl.makeBlock();
      blockType = b->getBlockType();
      nextBlockType = next->getBlockType();
      lvl.getGrid()->setLetter(nextBlockType);
      coords = b->getBlockCoord();
      lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
      view->update(coords, blockType);
      cout << lvl.getGrid() << endl;
      while (!isGameOver) {
        cin >> cmd;
        if (cmd == "a"){
          view->update(coords, ' ');
          b->left();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "d"){
          view->update(coords, ' ');
          b->right();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "s"){
          view->update(coords, ' ');
          b->down();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "x"){
          view->update(coords, ' ');
          b->drop();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          lvl.getGrid()->rowClear(coords);
          view->update(coords, blockType);
          delete b;
          b = next;
          next = lvl.makeBlock();
          coords = b->getBlockCoord();
          blockType = b->getBlockType();
          nextBlockType = next->getBlockType();
          lvl.getGrid()->setLetter(nextBlockType);
          isGameOver = lvl.getGrid()->gameOver(coords);
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
          view->update(coords, blockType);
        } else if (cmd == "c"){
          view->update(coords, ' ');
          b->clockwise();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        } else if (cmd == "z"){
          view->update(coords, ' ');
          b->counterclockwise();
          coords = b->getBlockCoord();
          lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
          view->update(coords, blockType);
        }
        cout << lvl.getGrid() << endl;
      } // while !isGameOver
      delete b; 
      delete next;
    }
    delete window;
    delete view; // else
  } // try
  catch (ios::failure &) {
  }*/
}