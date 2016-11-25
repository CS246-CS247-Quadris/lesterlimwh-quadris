class Iblock {
	BlockCoord coords;
	bool isHeavy;
	Grid *g;
	int orientation = 0;
	const char name = 'I';

public:
	Iblock(BlockCoord coords, bool isHeavy, Grid *g);
	void left() override;
	void right() override;
	void down() override;
	void counterclockwise() override;
	void clockwise() override;
	void drop() override;
};