#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "Tile.h"

class BoardTile : public Tile {
public:
	// Constructors
    BoardTile() : hit_(false), ship_(false) { }
    BoardTile(char c, char r) : Tile(c, r), hit_(false), ship_(false) { }

    bool getHit() const;
    void setHit();

    bool getShip() const;
    void setShip();

private:
    bool hit_;
    bool ship_;
};

inline bool BoardTile::getHit() const {
    return hit_;
}

inline void BoardTile::setHit() {
    hit_ = true;
}

inline bool BoardTile::getShip() const {
    return ship_;
}

inline void BoardTile::setShip() {
    ship_ = true;
}

#endif // BOARDTILE_H



