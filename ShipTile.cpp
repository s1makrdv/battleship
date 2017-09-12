#include "ShipTile.h"


ShipTile::ShipTile() :
  h_(false)
{

}

ShipTile::ShipTile(char c, char r) :
  Tile(c, r),
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
