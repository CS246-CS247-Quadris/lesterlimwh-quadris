#include <iostream>
#include "controller.h"
#include <regex>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char * argv[]) {
  cout << "Please enter a level: ";
  int n;
  cin >> n;
  cout << endl; 

  while (true){
    if (n == 0){
      Controller ctrl(n, "test.txt"); // change test.txt to sequence.txt when done testing
      if (argc > 1){
        for(int i = 1; i < argc; ++i){
          string theArg = argv[i];
          if (theArg == "-text"){
            ctrl.noDisplayGame();
          } else if (theArg == "-seed"){
            ctrl.startGame();
          } else if (theArg == "-scriptfile"){
            ctrl.startGame();
          } else if (theArg == "-startlevel"){
            ctrl.startGame();
          } else{
            ctrl.startGame();
          }
        }
      } else{
        ctrl.startGame();
      }
      break;
    } else if (n == 1 || n == 2 || n == 3 || n == 4){
      Controller ctrl(n);
      if (argc > 1){
        for(int i = 1; i < argc; ++i){
          string theArg = argv[i];
          if (theArg == "-text"){
            ctrl.noDisplayGame();
          } else if (theArg == "-seed"){
            ctrl.startGame();
          } else if (theArg == "-scriptfile"){
            ctrl.startGame();
          } else if (theArg == "-startlevel"){
            ctrl.startGame();
          } else{
            ctrl.startGame();
          }
        }
      } else{
        ctrl.startGame();
      }
      break;
    } else{
      cout << "Invalid level. ";
    }
  }
}