#include "graphics.h"
Graphics::Graphics(Xwindow &window, int rows, int columns): window{window}, rows{rows}, columns{columns}{
	width = 500/rows;
	window.drawLine(100, 150, 100, 650);
	window.drawLine(width * 15 - 10, 150, width * 15 - 10, 650);
	window.drawLine(100, 150, width * 15 - 10, 150);
	window.drawLine(100, 650, width * 15 - 10, 650);
	
}

Graphics::~Graphics(){}
void Graphics::update(const BlockCoord &b, const char blockType){
	int colour;
	if (blockType == 'I'){ colour = Xwindow::Orange; }
	else if (blockType == 'J'){ colour = Xwindow::Blue; }
	else if (blockType == 'L'){ colour = Xwindow::Green; }
	else if (blockType == 'O'){ colour = Xwindow::Red; }
	else if (blockType == 'S'){ colour = Xwindow::Cyan; }
	else if (blockType == 'Z'){ colour = Xwindow::Yellow; }
	else if (blockType == ' '){ colour = Xwindow::White; }
	else { colour = Xwindow::Magenta; }
	window.fillRectangle(100 + b.x1.x*width, 150 + 13 + (17 - b.x1.y)*width, width, width, colour);
	window.fillRectangle(100 + b.x2.x*width, 150 + 13 + (17 - b.x2.y)*width, width, width, colour);
	window.fillRectangle(100 + b.x3.x*width, 150 + 13 + (17 - b.x3.y)*width, width, width, colour);
	window.fillRectangle(100 + b.x4.x*width, 150 + 13 + (17 - b.x4.y)*width, width, width, colour);
}
