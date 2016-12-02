#include "window.h"
#include "blockcoord.h"
#include "graphiccell.h"
#include <vector>
class Graphics{
	Xwindow &window;
	int rows;
	int columns;
	int totalw = 500;
	int totalh = 800;
	int startIndent = 200;
	double width;
	std::vector<std:: vector <GraphicCell> > view;
public:
	Graphics(Xwindow &window, int rows, int columns);
	~Graphics();
	void rowClear(std::vector<int>);
	void update(const BlockCoord &b, const char blockType);
	void gameOver(int score);
	int getColour(const char blockType);
	void print();
};