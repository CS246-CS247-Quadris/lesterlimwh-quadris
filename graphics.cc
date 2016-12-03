#include "graphics.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
Graphics::Graphics(Xwindow &window, int rows, int columns, Grid *g): window{window}, rows{rows}, columns{columns}, g{g}{
	window.drawBigString(300, 50, "Quadris", Xwindow::Black);
	width = 500/rows;
	//view = std::vector< std::vector <GraphicCell > > (rows, std::vector <GraphicCell> (columns));
	/*for (int j = 0; j < rows; ++j){
		for (int i = 0; i < columns; ++i){
			//view[j][i].x = i; //100 + i*width;
			//view[j][i].y = j; //150 + 13 + (17 - j)*width;
			view[j][i].letter = ' ';
			view[j][i].isChanged = false;
			//window.drawRectangle(i*width + 100, (17 - j)*width + 150 + 13, width, width);
		}
	}*/
	
}

Graphics::~Graphics(){}

//void Graphics::update(const BlockCoord &b, const char blockType){
	/*int colour;
	if (blockType == 'I'){ colour = Xwindow::Orange; }
	else if (blockType == 'J'){ colour = Xwindow::Blue; }
	else if (blockType == 'L'){ colour = Xwindow::Green; }
	else if (blockType == 'O'){ colour = Xwindow::Red; }
	else if (blockType == 'S'){ colour = Xwindow::Cyan; }
	else if (blockType == 'Z'){ colour = Xwindow::Yellow; }
	else if (blockType == ' '){ colour = Xwindow::White; }
	else { colour = Xwindow::Magenta; } */
	/*view[b.x1.y][b.x1.x].letter = blockType;
	view[b.x1.y][b.x1.x].isChanged = true;
	view[b.x2.y][b.x2.x].letter = blockType;
	view[b.x2.y][b.x2.x].isChanged = true;
	view[b.x3.y][b.x3.x].letter = blockType;
	view[b.x3.y][b.x3.x].isChanged = true;
	view[b.x4.y][b.x4.x].letter = blockType;
	view[b.x4.y][b.x4.x].isChanged = true; */
	//window.fillRectangle(100 + b.x1.x*width, 150 + 13 + (17 - b.x1.y)*width, width, width, colour);
	//window.fillRectangle(100 + b.x2.x*width, 150 + 13 + (17 - b.x2.y)*width, width, width, colour);
	//window.fillRectangle(100 + b.x3.x*width, 150 + 13 + (17 - b.x3.y)*width, width, width, colour);
	//window.fillRectangle(100 + b.x4.x*width, 150 + 13 + (17 - b.x4.y)*width, width, width, colour);
//}

void Graphics::levelChanged(){
	isLvlDif = true;
}

int Graphics::getColour(const char blockType){
	int colour;
	if (blockType == 'I'){ colour = Xwindow::Orange; }
	else if (blockType == 'J'){ colour = Xwindow::Blue; }
	else if (blockType == 'L'){ colour = Xwindow::Green; }
	else if (blockType == 'O'){ colour = Xwindow::Red; }
	else if (blockType == 'S'){ colour = Xwindow::Cyan; }
	else if (blockType == 'Z'){ colour = Xwindow::Yellow; }
	else if (blockType == 'T'){ colour = Xwindow::Magenta; }
	else if (blockType == '*'){ colour = Xwindow::Brown; }
	else { colour = Xwindow::White; }
	return colour;
}

void Graphics::gameOver(int score){
	std::string scoreView;
	std::stringstream ss{scoreView};
	ss << "Final score is ";
	ss << score;
	//scoreView << score;
	window.fillRectangle(0, 0, 800, 800, Xwindow::Black);
	window.drawString(300,250, "You reached the top :(", Xwindow::White);
	window.drawString(300, 300, ss.str(), Xwindow::White );
}

/*void Graphics::rowClear(const std::vector<int> delRows){
	int size = delRows.size();
	if (size >= 1){ isScoreDif = 1; }
	for (int i = 0; i < size; ++i){
		view.erase(view.begin() + delRows[i]);
		view.emplace_back(std::vector<GraphicCell>(columns));
		for (int l = 0; l < columns; ++l){
			//view[l][0].x = l; //100 + l*width;
			//view[l][0].y = 0; //150 + 13 + (17 - (size - l))*width;
			view[rows - 1][l].letter = ' ';
			view[rows - 1][l].isChanged = false;
		}
		for (int k = delRows[i]; k < rows; ++k){
			for (int j = 0; j < columns; ++j){
				view[k][j].isChanged = true;
			}
		}
	}
}*/

void Graphics::print(int score, int dif){
	int colour;
	if (isScoreDif){
		window.fillRectangle(550, 380, 300, 40, Xwindow::White);
		std::string theScore;
		std::stringstream ss{theScore};
		ss << "Score: ";
		ss << score;
		window.drawString(600,400, ss.str(), Xwindow::Black); 
		isScoreDif = false;
    }
    if (isLvlDif){
    	window.fillRectangle(550, 280, 300, 40, Xwindow::White);
    	std::string level;
    	std::stringstream ss2{level};
    	ss2 << "Level: ";
    	ss2 << dif;
    	window.drawString(600,300, ss2.str(), Xwindow::Black);
    	isLvlDif = false; 
    }
	/*for (int j = 0; j < rows; ++j){
		for (int i = 0; i < columns; ++i){
			if (view[j][i].isChanged){
				colour = getColour(view[j][i].letter);
				//window.drawRectangle(i*width + 100, (17 - j)*width + 150 + 13, width, width);
				window.fillRectangle(i*width + 100, (17 - j)*width + 150 + 13, width, width, colour );
				view[j][i].isChanged = false;
			}
		}
	}*/
	for (int i = 0; i < g->height; ++i){
		for (int j = 0; j < g->width; ++j){
			if (g->display[i][j].isChanged){
				colour = getColour(g->display[i][j].letter);
				//window.drawRectangle(i*width + 100, (17 - j)*width + 150 + 13, width, width);
				window.fillRectangle(j*width + 100, (17 - i)*width + 150 + 13, width, width, colour );
				g->display[i][j].isChanged = false;
			}
		}
	}
	window.drawLine(100, 150, 100, 650);
	window.drawLine(width * 15 - 10, 150, width * 15 - 10, 650);
	window.drawLine(100, 150, width * 15 - 10, 150);
	window.drawLine(100, 650, width * 15 - 10, 650);

}
