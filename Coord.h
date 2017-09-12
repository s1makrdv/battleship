#ifndef COORD_H
#define COORD_H

typedef struct coord
{
  coord() : col(0), row(0) { }
  coord(char c, char r) : col(c), row(r) { }

  char col;
  char row;
} coord_t;

#endif // COORD_H
