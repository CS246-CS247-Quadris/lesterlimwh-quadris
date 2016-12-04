#include "controller.h"

using std::regex;
using std::smatch;
using std::regex_match;
using std::istringstream;

Controller::Controller(int levelNum): levelNum{levelNum} {
	lvl = new Level(levelNum);
}

Controller::Controller(int levelNum, string file): levelNum{levelNum}, file{file} {
	lvl = new Level(levelNum, file);
}

Controller::~Controller(){ delete lvl; }

void Controller::noDisplayGame(){
	if (levelNum == 0){
		lvl->readInFile();
	}

	string cmd;
    bool isGameOver = false;
   	bool noRandom = false;
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
		regex r("^[0-9]*(ri|rig|righ|right)");
		regex l("^[0-9]*(le|lef|left)");
		regex d("^[0-9]*(do|dow|down)");
		regex dr("^[0-9]*(dr|dro|drop)");
		regex c("^[0-9]*(clock|clockw|clockwi|clockwis|clockwise)");
		regex cc("^[0-9]*(counter|counterc|countercl|counterclo|countercloc|counterclock|counterclockw|counterclockwi|counterclockwis|counterclockwise)");
		regex lu("^[0-9]*(levelu|levelup)");
		regex ld("^[0-9]*(leveld|leveldo|leveldow|leveldown)");
		regex blocks("^[IJLOSTZ]");
		smatch m;

		if (regex_match(cmd, m, l)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->left();
				}
			} else{
				b->left();
			}
			if (b->getHeavy()){
				b->down();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, r)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->right();
				}
			} else{
				b->right();
			}
			if (b->getHeavy()){
				b->down();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, d)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->down();
				}
			} else{
				b->down();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, c)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->clockwise();
				}
			} else{
				b->clockwise();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, cc)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->counterclockwise();
				}
			} else{
				b->counterclockwise();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, dr)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->drop();
					coords = b->getBlockCoord();
					lvl->getGrid()->addTolvl4Count();
					lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
					delete b;
					b = next;
					next = lvl->makeBlock(noRandom);
					coords = b->getBlockCoord();
					blockType = b->getBlockType();
					nextBlockType = next->getBlockType();
					lvl->getGrid()->setLetter(nextBlockType);
					isGameOver = lvl->getGrid()->gameOver(coords);
					if (isGameOver){ break; }
					lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
				}
				if (isGameOver) { break; }
			} else{
				b->drop();
				coords = b->getBlockCoord();
				lvl->getGrid()->addTolvl4Count();
				lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
				delete b;
				b = next;
				next = lvl->makeBlock(noRandom);
				coords = b->getBlockCoord();
				blockType = b->getBlockType();
				nextBlockType = next->getBlockType();
				lvl->getGrid()->setLetter(nextBlockType);
				isGameOver = lvl->getGrid()->gameOver(coords);
				if (isGameOver){ break; }
				lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
			}
		} else if (regex_match(cmd, m, lu)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					lvl->levelUp();
				}
			} else{
				lvl->levelUp();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, ld)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					lvl->levelDown();
				}
			} else{
				lvl->levelDown();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, blocks)){
			delete b;
			if (cmd == "I") { b = lvl->iBlock(); }
			else if (cmd == "J") { b = lvl->jBlock(); }
			else if (cmd == "L") { b = lvl->lBlock(); }
			else if (cmd == "O") { b = lvl->oBlock(); }
			else if (cmd == "S") { b = lvl->sBlock(); }
			else if (cmd == "T") { b = lvl->tBlock(); }
			else { b = lvl->zBlock(); }
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
		} else if (cmd == "norandom"){
			cin >> cmd;
			lvl->readRandomFile(cmd);
			coords = b->getBlockCoord();
			lvl->getGrid()->removeBlock(coords, lvl->getDif());
			delete b;
			delete next;
			noRandom = true;
			b = lvl->makeBlock(noRandom);
			next = lvl->makeBlock(noRandom);
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl->getGrid()->setLetter(nextBlockType);
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
		} else if (cmd == "restart"){
			lvl->getGrid()->restart();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		}
		cout << lvl->getGrid() << endl;		
	}
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
    bool isGameOver = false;
    bool noRandom = false;
	Block * b = lvl->makeBlock();
	Block * next = lvl->makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();

	lvl->getGrid()->setLetter(nextBlockType);
	Xwindow *window = new Xwindow();
    Graphics *view = new Graphics(*window, rows, columns, lvl->getGrid());
	BlockCoord coords = b->getBlockCoord();
	BlockCoord nextcoords = next->getBlockCoord();
	lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
	view->drawNextBlock(nextcoords, nextBlockType);
	cout << lvl->getGrid() << endl;
	cout << coords.x1.x << coords.x1.y << endl;
	view->print(lvl->getGrid()->getScore(), lvl->getDif());
	std::vector<int> delRows;

	while (true){
		cin >> cmd;
		regex r("^[0-9]*(ri|rig|righ|right)");
		regex l("^[0-9]*(le|lef|left)");
		regex d("^[0-9]*(do|dow|down)");
		regex dr("^[0-9]*(dr|dro|drop)");
		regex c("^[0-9]*(clock|clockw|clockwi|clockwis|clockwise)");
		regex cc("^[0-9]*(counter|counterc|countercl|counterclo|countercloc|counterclock|counterclockw|counterclockwi|counterclockwis|counterclockwise)");
		regex lu("^[0-9]*(levelu|levelup)");
		regex ld("^[0-9]*(leveld|leveldo|leveldow|leveldown)");
		regex blocks("^[IJLOSTZ]");
		smatch m;

		if (regex_match(cmd, m, l)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->left();
				}
			} else{
				b->left();
			}
			if (b->getHeavy()){
				b->down();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, r)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->right();
				}
			} else{
				b->right();
			}
			if (b->getHeavy()){
				b->down();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, d)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->down();
				}
			} else{
				b->down();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, c)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->clockwise();
				}
			} else{
				b->clockwise();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, cc)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->counterclockwise();
				}
			} else{
				b->counterclockwise();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, dr)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					b->drop();
					coords = b->getBlockCoord();
					lvl->getGrid()->addTolvl4Count();
					lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
					lvl->getGrid()->rowClear(b->getBlockCoord());
					delete b;
					b = next;
					next = lvl->makeBlock(noRandom);
					coords = b->getBlockCoord();
					blockType = b->getBlockType();
					nextBlockType = next->getBlockType();
					lvl->getGrid()->setLetter(nextBlockType);
					view->drawNextBlock(nextcoords, nextBlockType);
					isGameOver = lvl->getGrid()->gameOver(coords);
					if (isGameOver){ break; }
					lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
				}
				if (isGameOver) { break; }
			} else{
				b->drop();
				coords = b->getBlockCoord();
				lvl->getGrid()->addTolvl4Count();
				lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
				lvl->getGrid()->rowClear(b->getBlockCoord());
				delete b;
				b = next;
				next = lvl->makeBlock(noRandom);
				coords = b->getBlockCoord();
				blockType = b->getBlockType();
				nextBlockType = next->getBlockType();
				lvl->getGrid()->setLetter(nextBlockType);
				view->drawNextBlock(nextcoords, nextBlockType);
				isGameOver = lvl->getGrid()->gameOver(coords);
				if (isGameOver){ break; }
				lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
			}
		} else if (regex_match(cmd, m, lu)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					lvl->levelUp();
				}
			} else{
				lvl->levelUp();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, ld)){
			string s = cmd.substr(0,1);
			istringstream ss(s);
			int units;
			if (ss >> units){
				for (int i = 0; i < units; ++i){
					lvl->levelDown();
				}
			} else{
				lvl->levelDown();
			}
			coords = b->getBlockCoord();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		} else if (regex_match(cmd, m, blocks)){
			delete b;
			if (cmd == "I") { b = lvl->iBlock(); }
			else if (cmd == "J") { b = lvl->jBlock(); }
			else if (cmd == "L") { b = lvl->lBlock(); }
			else if (cmd == "O") { b = lvl->oBlock(); }
			else if (cmd == "S") { b = lvl->sBlock(); }
			else if (cmd == "T") { b = lvl->tBlock(); }
			else { b = lvl->zBlock(); }
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
		} else if (cmd == "norandom"){
			cin >> cmd;
			lvl->readRandomFile(cmd);
			coords = b->getBlockCoord();
			lvl->getGrid()->removeBlock(coords, lvl->getDif());
			delete b;
			delete next;
			noRandom = true;
			b = lvl->makeBlock(noRandom);
			next = lvl->makeBlock(noRandom);
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			nextBlockType = next->getBlockType();
			lvl->getGrid()->setLetter(nextBlockType);
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false); 
		} else if (cmd == "restart"){
			lvl->getGrid()->restart();
			coords = b->getBlockCoord();
			blockType = b->getBlockType();
			lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
		}
		cout << lvl->getGrid() << endl;
		view->print(lvl->getGrid()->getScore(), lvl->getDif());	
	}

    view->gameOver(lvl->getGrid()->getScore());
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	delete b;
	delete next;
	delete window;
	delete view;
}

