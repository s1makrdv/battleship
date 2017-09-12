#include "ShipTile.h"


ShipTile::ShipTile() :
  h_(false)
{

}

ShipTile::ShipTile(char col, char row) :
  Tile(col, row),
  h_(false)
{

}

bool ShipTile::getHit() const
{
  return h_;
}

void ShipTile::setHit()
{
  h_ = true;
}
