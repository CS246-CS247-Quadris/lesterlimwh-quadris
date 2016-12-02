#include "controller.h"

Controller::Controller(int levelNum): levelNum{levelNum} {}

Controller::Controller(int levelNum, string file): levelNum{levelNum}, file{file} {}

void Controller::startGame(){
	if (levelNum == 0){
		Level lvl(levelNum, file);
		createGame(lvl);
	} else{
		Level lvl(levelNum);
		createGame(lvl);
	}
}

void Controller::levelUp(){
}

void Controller::levelDown(){
}

void Controller::createGame(Level lvl){
	string cmd;
	int rows = 18;
	int columns = 11;
	Xwindow *window = new Xwindow();
    Graphics *view = new Graphics(*window, rows, columns);

	if (levelNum == 0) {
		lvl.readInFile();
	}

    bool isGameOver = false;
	Block * b = lvl.makeBlock();
	Block * next = lvl.makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl.getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
	view->update(coords, blockType);
	cout << lvl.getGrid() << endl;

	while (true){
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
		} else if (cmd == "x"){
			view->update(coords, ' ');
			b->drop();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
			view->update(coords, blockType);
			lvl.getGrid()->rowClear(coords);
			delete b;
			b = next;
			next = lvl.makeBlock();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl.getGrid()->setLetter(nextBlockType);
			isGameOver = lvl.getGrid()->gameOver(coords);
			if (isGameOver) { break; }
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
			view->update(coords, blockType);
		}
		cout << lvl.getGrid() << endl;
		
	}
	if (isGameOver){
		view->gameOver(lvl.getGrid()->getScore());
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}

	delete b;
	delete next;
	delete window;
	delete view;
}

/*void Controller::levelZeroGame(){
	string cmd;
	int rows = 18;
	int columns = 11;
	Xwindow *window = new Xwindow();
    Graphics *view = new Graphics(*window, rows, columns);

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
	view->update(coords, blockType);
	cout << lvl.getGrid() << endl;

	while (true){
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
		} else if (cmd == "x"){
			view->update(coords, ' ');
			b->drop();
			coords = b->getBlockCoord();
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
			view->update(coords, blockType);
			lvl.getGrid()->rowClear(coords);
			delete b;
			b = next;
			next = lvl.makeBlock();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl.getGrid()->setLetter(nextBlockType);
			isGameOver = lvl.getGrid()->gameOver(coords);
			if (isGameOver) { break; }
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
			view->update(coords, blockType);
		}
		cout << lvl.getGrid() << endl;
		
	}
	if (isGameOver){
		view->gameOver(lvl.getGrid()->getScore());
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}

	delete b;
	delete next;
	delete window;
	delete view;
}

void Controller::regularGame(){
    string cmd;
    int rows = 18;
	int columns = 11;
    Xwindow *window = new Xwindow();
    Graphics *view = new Graphics(*window, rows, columns);

	Level lvl(levelNum);
    bool isGameOver = false;
	Block * b = lvl.makeBlock();
	Block * next = lvl.makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl.getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	lvl.getGrid()->update(coords, blockType, lvl.getDif(), false);
	view->update(coords, blockType);
	cout << lvl.getGrid() << endl;

	while (true){
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
			if (isGameOver){ break; }
			lvl.getGrid()->update(coords, blockType, lvl.getDif(), false); 
			view->update(coords, blockType);
		}
		cout << lvl.getGrid() << endl;
		
	}
    view->gameOver(lvl.getGrid()->getScore());
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	delete b;
	delete next;
	delete window;
	delete view;	
}*/
