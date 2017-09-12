#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "Tile.h"

class BoardTile : public Tile {
public:
    BoardTile();
    BoardTile(char c, char r);

    bool getHit() const;
    void setHit();

    bool getShip() const;
    void setShip();

private:
    bool hit_;
    bool ship_;
};









#endif // BOARDTILE_H



