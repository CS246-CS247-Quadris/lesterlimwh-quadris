#include <iostream>
#include "controller.h"
#include <regex>

using std::cin;
using std::cout;
using std::endl;
using std::istringstream;

int main(int argc, char * argv[]) {

  int level;
  bool levelSet = false;

  if (argc > 1){
    for (int i = 1; i < argc; ++i){
      string theArg = argv[i];
      if (theArg == "-startlevel"){
        if (i < argc - 1){
          ++i;
          theArg = argv[i];
          istringstream ss(theArg);
          int lvl;
          if (ss >> lvl){
            level = lvl;
          }
        } else{
          level = 0;
        }
        levelSet = true;
      }
    }
  }

  if (!levelSet){
    cout << "Please enter a level: ";
    cin >> level;
    cout << endl;     
  }

  int gameType = 0; // 0 => No Display, 1 => With Display
  if (level != 0) gameType = 1;

  if (level == 0){
    srand(time(NULL));
    Controller ctrl(level, "sequence.txt");
    if (argc > 1){
      for (int i = 1; i < argc; ++i){
        string theArg = argv[i];
        if (theArg == "-text"){
          gameType = 0;
        } 
        if (theArg == "-seed"){
          ++i;
          theArg = argv[i];
          istringstream ss(theArg);
          int seed;
          if (ss >> seed){
            srand(seed); 
          }
        } 
        if (theArg == "-scriptfile"){
          ++i;
          theArg = argv[i];
          ctrl.changeFile(theArg);
        }
      }
    }
    if (gameType == 0) {
      ctrl.noDisplayGame();
    } else{
      ctrl.startGame();
    }
  } else if (level == 1 || level == 2 || level == 3 || level == 4){
    srand(time(NULL));
    Controller ctrl(level);
    if (argc > 1){
      for (int i = 1; i < argc; ++i){
        string theArg = argv[i];
        if (theArg == "-text"){
          gameType = 0;
        } 
        if (theArg == "-seed"){
          ++i;
          theArg = argv[i];
          istringstream ss(theArg);
          int seed;
          if (ss >> seed){
            srand(seed); 
          }
        } 
        if (theArg == "-scriptfile"){
          ++i;
          theArg = argv[i];
          ctrl.changeFile(theArg);
        }
      }
    }
    if (gameType == 0) {
      ctrl.noDisplayGame();
    } else{
      ctrl.startGame();
    }
  }
}
