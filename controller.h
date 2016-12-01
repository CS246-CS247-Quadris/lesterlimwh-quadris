#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "level.h"
#include <string>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Controller{
	int levelNum;
	string file;
public:
	Controller(int levelNum);
	Controller(int levelNum, string file);
	void startGame();
	void regularGame();
	void levelZeroGame();
};

#endif