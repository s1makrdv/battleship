#ifndef TILE_H
#define TILE_H

class Tile
{
  public:
    Tile();
    Tile(char c, char r);

    char getCol() const;
    char getRow() const;

  private:
    char col_, row_;
};

#endif // TILE_H


