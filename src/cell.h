// Copyright 2015 Robert Bittle(guywithnose@gmail.com)
#ifndef CELL_H_
#define CELL_H_
#include <stdint.h>

struct Position {
    int64_t x;
    int64_t y;

    Position(int64_t x, int64_t y);
    Position();
};

class Cell {
 public:
    Position position;
    bool wasAlive;
    int neighbors;

    Cell(Position position, bool wasAlive);
};
#endif  // CELL_H_
