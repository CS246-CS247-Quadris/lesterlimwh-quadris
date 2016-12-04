#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <string>
#include <fstream>
#include <iostream>
#include "level.h"
#include "window.h"
#include "graphics.h"
#include <chrono>
#include <thread>
#include <regex>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Controller{
	int levelNum;
	string file;
	Level * lvl;
public:
	Controller(int levelNum);
	Controller(int levelNum, string file);
	void startGame();
	void noDisplayGame();
	~Controller();
};

#endif