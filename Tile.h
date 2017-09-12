#ifndef TILE_H
#define TILE_H

class Tile
{
  public:
    Tile();
    Tile(char col, char row);

    char getCol() const;
    char getRow() const;

  private:
    char col_, row_;
};

#endif // TILE_H


