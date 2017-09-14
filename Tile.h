#ifndef TILE_H
#define TILE_H

class Tile
{
  public:
    Tile() : col_(0), row_(0) { }
    Tile(char col, char row) : col_(col), row_(row) { }

    char getCol() const;
    char getRow() const;

  private:
    char col_, row_;
};

inline char Tile::getCol() const
{
  return col_;
}

inline char Tile::getRow() const
{
  return row_;
}


#endif // TILE_H
