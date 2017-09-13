#ifndef COORD_H
#define COORD_H

const char firstColChar = 'A';
const char lastColChar = 'J';

typedef struct coord
{
  coord() : col(0), row(0) { }
  coord(char c, char r) : col(c), row(r) { }

  char col;
  char row;
} coord_t;

#endif // COORD_H
