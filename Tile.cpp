#include "Tile.h"

Tile::Tile() :
  col_(0),
  row_(0)
{

}

Tile::Tile(char col, char row) :
  col_(col),
  row_(row)
{

}

char Tile::getCol() const
{
  return col_;
}

char Tile::getRow() const
{
  return row_;
}
