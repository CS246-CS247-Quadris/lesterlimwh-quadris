class Block {
public:
	virtual void left() = 0;
	virtual void right() = 0;
	virtual void down() = 0;
	virtual void counterclockwise() = 0;
	virtual void clockwise() = 0;
	virtual void drop() = 0;
	virtual ~Block() = 0;
};