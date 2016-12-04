#include "graphics.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
Graphics::Graphics(Xwindow &window, int rows, int columns, Grid *g): window{window}, rows{rows}, columns{columns}, g{g}{
	window.drawBigString(300, 50, "Quadris", Xwindow::Black);
	width = 500/rows;
}

Graphics::~Graphics(){}

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

void Graphics::endOfFile(int score){
	std::string scoreView;
	std::stringstream ss{scoreView};
	ss << "Final score is ";
	ss << score;
	//scoreView << score;
	window.fillRectangle(0, 0, 800, 800, Xwindow::Black);
	window.drawString(300,250, "You reached end of file", Xwindow::White);
	window.drawString(300, 300, ss.str(), Xwindow::White );
}

void Graphics::drawNextBlock(const BlockCoord &b, const char BlockType){
	window.fillRectangle(50, 660, 450,300, Xwindow::White);
	window.drawBigString(40, 720, "Next Block: ", Xwindow::Black);
	int colour = getColour(BlockType);
	window.fillRectangle(b.x1.x*width + 100, (17-b.x1.y)*width + 650, width, width, colour );
	window.fillRectangle(b.x2.x*width + 100, (17-b.x2.y)*width + 650, width, width, colour );
	window.fillRectangle(b.x3.x*width + 100, (17-b.x3.y)*width + 650, width, width, colour );
	window.fillRectangle(b.x4.x*width + 100, (17-b.x4.y)*width + 650, width, width, colour );
} 

void Graphics::print(int score, int dif){
	int colour;
	if (g->isScoreDif){
		window.fillRectangle(550, 380, 300, 40, Xwindow::White);
		std::string theScore;
		std::stringstream ss{theScore};
		ss << "Score: ";
		ss << score;
		window.drawString(600,400, ss.str(), Xwindow::Black); 
		g->isScoreDif = false;
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
