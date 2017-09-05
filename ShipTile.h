#ifndef SHIPTILE_H
#define SHIPTILE_H

#include "Tile.h"

class ShipTile : public Tile
{
  public:
    // Constructor
    ShipTile() : h_(false) { }
    ShipTile(char c, char r) : Tile(c, r), h_(false) { }

    bool getHit() const;
    void setHit();

  private:
    bool h_;
};

inline bool ShipTile::getHit() const
{
    return h_;
}

inline void ShipTile::setHit()
{
    h_ = true;
}

#endif // SHIPTILE_H

