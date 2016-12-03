#include "controller.h"

Controller::Controller(int levelNum): levelNum{levelNum} {
	lvl = new Level(levelNum);
}

Controller::Controller(int levelNum, string file): levelNum{levelNum}, file{file} {
	lvl = new Level(levelNum, file);
}

void Controller::noDisplayGame(){
	if (levelNum == 0){
		lvl->readInFile();
	}

	string cmd;
    bool isGameOver = false;
	Block * b = lvl->makeBlock();
	Block * next = lvl->makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl->getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
	cout << lvl->getGrid() << endl;
	cout << coords.x1.x << coords.x1.y << endl;

	while (true){
		cin >> cmd;
		if (cmd == "a"){
			b->left();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (cmd == "d"){
			b->right();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (cmd == "s"){
			b->down();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (cmd == "c"){
			b->clockwise();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (cmd == "z"){
			b->counterclockwise();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (cmd == "x"){
			b->drop();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			delete b;
			b = next;
			next = lvl->makeBlock();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl->getGrid()->setLetter(nextBlockType);
			isGameOver = lvl->getGrid()->gameOver(coords);
			if (isGameOver){ break; }
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
		} else if (cmd == "levelup"){
			lvl->levelUp();
		} else if (cmd == "leveldown"){
			lvl->levelDown();
		} else{
			std::regex r("^[0-9](right)");
			std::smatch m;
			if (std::regex_match(cmd, m, r)){
				string s = cmd.substr(0,1);
				std::istringstream ss(s);
				int units;
				ss >> units;
				for (int i = 0; i < units; ++i){
					b->right();
				}
				coords = b->getBlockCoord();
				lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			}
		}
		cout << lvl->getGrid() << endl;		
	}
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	delete b;
	delete next;
}

void Controller::startGame(){
	if (levelNum == 0){
		lvl->readInFile();
	}

	string cmd;
    int rows = 18;
	int columns = 11;
    Xwindow *window = new Xwindow();
    Graphics *view = new Graphics(*window, rows, columns);

    bool isGameOver = false;
	Block * b = lvl->makeBlock();
	Block * next = lvl->makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl->getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
	view->update(coords, blockType);
	cout << lvl->getGrid() << endl;
	cout << coords.x1.x << coords.x1.y << endl;
	view->print();
	std::vector<int> delRows;

	while (true){
		cin >> cmd;
		if (cmd == "a"){
			view->update(coords, ' ');
			b->left();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			view->update(coords, blockType);
		} else if (cmd == "d"){
			view->update(coords, ' ');
			b->right();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			view->update(coords, blockType);
		} else if (cmd == "s"){
			view->update(coords, ' ');
			b->down();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			view->update(coords, blockType);
		} else if (cmd == "c"){
			view->update(coords, ' ');
			b->clockwise();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			view->update(coords, blockType);
		} else if (cmd == "z"){
			view->update(coords, ' ');
			b->counterclockwise();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			view->update(coords, blockType);
		} else if (cmd == "x"){
			view->update(coords, ' ');
			b->drop();
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
			view->update(coords, blockType);
			delRows = lvl->getGrid()->rowClear(coords);
			view->rowClear(delRows);
			delete b;
			b = next;
			next = lvl->makeBlock();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl->getGrid()->setLetter(nextBlockType);
			isGameOver = lvl->getGrid()->gameOver(coords);
			if (isGameOver){ break; }
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
			view->update(coords, blockType);
		} else if (cmd == "levelup"){
			lvl->levelUp();
		} else if (cmd == "leveldown"){
			lvl->levelDown();
		}
		cout << lvl->getGrid() << endl;
		view->print();
		
	}

    view->gameOver(lvl->getGrid()->getScore());
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	delete b;
	delete next;
	delete window;
	delete view;
}

