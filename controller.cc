#include "controller.h"

Controller::Controller(int levelNum): levelNum{levelNum} {}

Controller::Controller(int levelNum, string file): levelNum{levelNum}, file{file} {}

void Controller::startGame(){
	levelNum == 0 ? levelZeroGame() : regularGame();
}

void Controller::levelZeroGame(){
	string cmd;
	Level lvl(levelNum, file);
	lvl.readInFile();
    bool isGameOver = false;
	Block * b = lvl.makeBlock();
	Block * next = lvl.makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl.getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
	cout << lvl.getGrid() << endl;

	while (!isGameOver){
		cin >> cmd;
		if (cmd == "a"){
			b->left();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "d"){
			b->right();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "s"){
			b->down();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "c"){
			b->clockwise();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "z"){
			b->counterclockwise();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "x"){
			b->drop();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
			lvl.getGrid()->rowClear(coords);
			delete b;
			b = next;
			next = lvl.makeBlock();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl.getGrid()->setLetter(nextBlockType);
			isGameOver = lvl.getGrid()->gameOver(coords);
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
		}
		cout << lvl.getGrid() << endl;
	}
}

void Controller::regularGame(){
    string cmd;
	Level lvl(levelNum);
    bool isGameOver = false;
	Block * b = lvl.makeBlock();
	Block * next = lvl.makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl.getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
	cout << lvl.getGrid() << endl;

	while (!isGameOver){
		cin >> cmd;
		if (cmd == "a"){
			b->left();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "d"){
			b->right();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "s"){
			b->down();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "c"){
			b->clockwise();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "z"){
			b->counterclockwise();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
		} else if (cmd == "x"){
			b->drop();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
			lvl.getGrid()->rowClear(coords);
			delete b;
			b = next;
			next = lvl.makeBlock();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl.getGrid()->setLetter(nextBlockType);
			isGameOver = lvl.getGrid()->gameOver(coords);
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
		}
		cout << lvl.getGrid() << endl;
	}
}