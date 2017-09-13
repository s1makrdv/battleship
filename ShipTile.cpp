#include "ShipTile.h"


ShipTile::ShipTile() :
  isHit_(false)
{

}

ShipTile::ShipTile(char col, char row) :
  Tile(col, row),
  isHit_(false)
{

}

bool ShipTile::getHit() const
{
  return isHit_;
}

void ShipTile::setHit()
{
  isHit_ = true;
}
