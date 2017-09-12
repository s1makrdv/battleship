#include "Tile.h"

Tile::Tile() :
  col_(0),
  row_(0)
{

}

Tile::Tile(char c, char r) :
  col_(c),
  row_(r)
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
