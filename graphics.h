#include "window.h"
#include "blockcoord.h"
#include "graphiccell.h"
#include <vector>
#include "grid.h"
class Graphics{
	Xwindow &window;
	int rows;
	int columns;
	int totalw = 500;
	int totalh = 800;
	int startIndent = 200;
	double width;
	Grid *g;
	bool isScoreDif = 1;
	bool isLvlDif = 1;
	std::vector<std:: vector <GraphicCell> > view;
public:
	Graphics(Xwindow &window, int rows, int columns, Grid *g);
	~Graphics();
	void levelChanged();
	//void rowClear(std::vector<int>);
	//void update(const BlockCoord &b, const char blockType);
	void drawNextBlock(const BlockCoord &b, const char BlockType);
	void gameOver(int score);
	int getColour(const char blockType);
	void print(int score, int dif);
};