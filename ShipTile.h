#ifndef SHIPTILE_H
#define SHIPTILE_H

#include "Tile.h"

class ShipTile : public Tile
{
  public:
    ShipTile();
    ShipTile(char col, char row);

    bool getHit() const;
    void setHit();

  private:
    bool isHit_;
};





#endif // SHIPTILE_H

