#ifndef SHIPTILE_H
#define SHIPTILE_H

#include "Tile.h"

class ShipTile : public Tile {
public:
	// Constructor
    ShipTile() : h_(false) { }
    ShipTile(char c, char r) : Tile(c, r), h_(false) { }

	void setHit() {
        h_ = true;
	}

	bool getHit() {
        return h_;
	}
private:
    bool h_;
};

#endif // SHIPTILE_H
