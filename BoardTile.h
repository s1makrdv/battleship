#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "Tile.h"

class BoardTile : public Tile {
public:
	// Constructors
    BoardTile() : hit_(false), ship_(false) { }
    BoardTile(char c, char r) : Tile(c, r), hit_(false), ship_(false) { }

	void setHit() {
        hit_ = true;
	}

	bool getHit() {
        return hit_;
	}

	bool getShip() {
        return ship_;
	}

	void setShip() {
        ship_ = true;
	}
private:
    bool hit_;
    bool ship_;
};

#endif // BOARDTILE_H
