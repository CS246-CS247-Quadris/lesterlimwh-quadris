#include "controller.h"

using std::regex;
using std::smatch;
using std::regex_match;
using std::ifstream;
using std::istringstream;

Controller::Controller(int levelNum): levelNum{levelNum} {
	lvl = new Level(levelNum);
}

Controller::Controller(int levelNum, string file): levelNum{levelNum}, file{file} {
	lvl = new Level(levelNum, file);
}

Controller::~Controller(){ delete lvl; }

// change the file that is read for Level 0 from sequence.txt to newFile
void Controller::changeFile(string newFile){ file = newFile; }

// noDisplayGame starts a new game without graphics display. 
// Contains functionality for the following commands: left, right, down, drop, 
// clockwise, counterclockwise, levelup, leveldown, restart, sequence, norandom, random, and hint.
// It is called when -text is passed as a command line argument.
void Controller::noDisplayGame(){
	if (levelNum == 0){
		lvl->readInFile();
	}

	string cmd;
	ifstream f;
	int seqCounter = -1;
   	bool readFromSeq = false;
    bool isGameOver = false;
   	bool noRandom = false;
   	bool endReached = false;
   	bool breakNextLoop = false;
	Block * b = lvl->makeBlock();
	Block * next = lvl->makeBlock();
	char blockType = b->getBlockType();
	char nextBlockType = next->getBlockType();
	lvl->getGrid()->setLetter(nextBlockType);
	BlockCoord coords = b->getBlockCoord();
	BlockCoord nextcoords = next->getBlockCoord();
	lvl->getGrid()->update(coords, blockType, lvl->getDif(), false);
	cout << lvl->getGrid() << endl;
	
	while (true){

		if (readFromSeq) { cmd = seqCommands[seqCounter]; } 
		else { cin >> cmd; }

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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
					try{
						next = lvl->makeBlock(noRandom);
					} catch (const char*){
						endReached = true;
						breakNextLoop = true;
						break;
					}
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
				lvl->getGrid()->rowClear(b->getBlockCoord());
				delete b;
				if (endReached == true){
					break;
				}
				b = next;
				coords = b->getBlockCoord();
				blockType = b->getBlockType();
				try{ 
				next = lvl->makeBlock(noRandom);
			} catch (const char*){
				endReached = true;
			}
				nextBlockType = next->getBlockType();
				nextcoords = next->getBlockCoord();
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
			if(lvl->getDif() == 0){
				lvl->readRandomFile("sequence.txt");
			}
		} else if (regex_match(cmd, m, blocks)){
			lvl->getGrid()->clearHint();
			coords = b->getBlockCoord();
			lvl->getGrid()->removeBlock(coords, lvl->getDif());
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
			if (readFromSeq) { 
				++seqCounter;
				cmd = seqCommands[seqCounter]; 
			} else{
				cin >> cmd;
			}
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
		} else if(cmd == "random"){
			coords = b->getBlockCoord();
			lvl->getGrid()->removeBlock(coords, lvl->getDif());
			delete b;
			delete next;
			noRandom = false;
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
		} else if (cmd == "hint"){
			lvl->getGrid()->update(b->hint(), '?', lvl->getDif(), false);
		} else if (cmd == "sequence"){
			readFromSeq = true;
			cin >> cmd;
			string s;
			f.open(cmd);
			while (f >> s){
				seqCommands.push_back(s);
				s.clear();
			}
		}
		if (seqCounter == seqCommands.size() - 1){
			readFromSeq = false;
			seqCounter = -1;
		} else{
			++seqCounter;
		}
		cout << lvl->getGrid() << endl;	
	}
	if (isGameOver){
		cout << "You have reached the top. Game is over" << endl;
	}
	else { 	cout << "You have reached end of file. Game is over" << endl; }	
	if (!(endReached)){
		delete b;
		delete  next;
	}
}

// startGame starts a new game with graphics display. 
// Contains functionality for the following commands: left, right, down, drop, 
// clockwise, counterclockwise, levelup, leveldown, restart, sequence, norandom, random, and hint.
void Controller::startGame(){
	if (levelNum == 0){
		lvl->readInFile();
	}
	string cmd;
    int rows = 18;
	int columns = 11;
	ifstream f;
	int seqCounter = -1;
   	bool readFromSeq = false;
    bool isGameOver = false;
    bool noRandom = false;
    bool endReached = false;
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
	view->print(lvl->getGrid()->getScore(), lvl->getDif());
	std::vector<int> delRows;

	while (true){

		if (readFromSeq) { cmd = seqCommands[seqCounter]; } 
		else { cin >> cmd; }

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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
			lvl->getGrid()->clearHint();
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
					try{
						next = lvl->makeBlock(noRandom);
					} catch(const char*){
						endReached = true;
						break;  // FIX THIS
					}
					
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
				view->print(lvl->getGrid()->getScore(), lvl->getDif());	
				lvl->getGrid()->rowClear(b->getBlockCoord());
				delete b;
				if (endReached == true){
					break;
				}
				b = next;
				coords = b->getBlockCoord();
				blockType = b->getBlockType();
				try{ 
				next = lvl->makeBlock(noRandom);
			} catch (const char*){
				endReached = true;
			}
				nextBlockType = next->getBlockType();
				nextcoords = next->getBlockCoord();
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
			view->levelChanged();
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
			view->levelChanged();
			if(lvl->getDif() == 0){
				lvl->readRandomFile("sequence.txt");
			}
		} else if (regex_match(cmd, m, blocks)){
			lvl->getGrid()->clearHint();
			coords = b->getBlockCoord();
			lvl->getGrid()->removeBlock(coords, lvl->getDif());
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
			if (readFromSeq) { 
				++seqCounter;
				cmd = seqCommands[seqCounter]; 
			} else{
				cin >> cmd;
			}
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
		} else if(cmd == "random"){
			coords = b->getBlockCoord();
			lvl->getGrid()->removeBlock(coords, lvl->getDif());
			delete b;
			delete next;
			noRandom = false;
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
		} else if (cmd == "hint"){
			lvl->getGrid()->update(b->hint(), '?', lvl->getDif(), false);
		} else if (cmd == "sequence"){
			readFromSeq = true;
			cin >> cmd;
			string s;
			f.open(cmd);
			while (f >> s){
				seqCommands.push_back(s);
				s.clear();
			}
		}
		if (seqCounter == seqCommands.size() - 1){
			readFromSeq = false;
			seqCounter = -1;
		} else{
			++seqCounter;
		}
		cout << lvl->getGrid() << endl;
		view->print(lvl->getGrid()->getScore(), lvl->getDif());	
	}
	if (endReached){
		view->endOfFile(lvl->getGrid()->getScore());
	}
	else {
    	view->gameOver(lvl->getGrid()->getScore());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	if (!(endReached)) { delete b; delete next; }
	delete window;
	delete view;
}
