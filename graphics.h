#include "window.h"
#include "blockcoord.h"

class Graphics{
	Xwindow &window;
	int rows;
	int columns;
	int totalw = 500;
	int totalh = 800;
	int startIndent = 200;
	double width;
public:
	Graphics(Xwindow &window, int rows, int columns);
	~Graphics();
	void update(const BlockCoord &b, const char blockType);
	void gameOver(int score);
};