#ifndef SHIPTILE_H
#define SHIPTILE_H

#include "Tile.h"

class ShipTile : public Tile
{
  public:
    ShipTile();
    ShipTile(char c, char r);

    bool getHit() const;
    void setHit();

  private:
    bool h_;
};





#endif // SHIPTILE_H

