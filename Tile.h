#ifndef TILE_H
#define TILE_H

class Tile {
public:
	// Constructor
    Tile() : col_(0), row_(0) { }
    Tile(char c, char r) : col_(c), row_(r) { }

	char getCol() {
        return col_;
	}

	char getRow() {
        return row_;
	}

	bool valid() {
        return col_;
	}

private:
    char col_, row_;
};

#endif // TILE_H
