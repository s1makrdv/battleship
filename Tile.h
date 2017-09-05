#ifndef TILE_H
#define TILE_H

class Tile
{
  public:
    // Constructor
    Tile() : col_(0), row_(0) { }
    Tile(char c, char r) : col_(c), row_(r) { }

    char getCol() const;
    char getRow() const;

    bool valid() const;

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

inline bool Tile::valid() const
{
  return col_;
}

#endif // TILE_H


