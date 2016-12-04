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
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Controller{
	int levelNum;
	string file;
	Level * lvl;
	vector<string> seqCommands;

public:
	Controller(int levelNum);
	Controller(int levelNum, string file);
	void changeFile(string newFile);
	void startGame();
	void noDisplayGame();
	~Controller();
};

#endif