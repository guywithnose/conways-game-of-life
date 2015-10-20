// Copyright 2015 Robert Bittle(guywithnose@gmail.com)
#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include <map>
#include "./cell.h"
#include "./cursesDisplay.h"

using std::map;
using std::ostream;

struct comparePositions {
    bool operator()(const Position& a, const Position& b) const {
        if (a.x < b.x) {
            return true;
        }

        if (a.x == b.x && a.y < b.y) {
            return true;
        }

        return false;
    }
};

typedef map<Position, Cell*, comparePositions> cellMap;

class Board {
 public:
     cellMap cells;
     Board* next();
     void addCell(Cell* cell);
     void feed(Position position);
     void wasAlive(Position position);
     void display(CursesDisplay* cursesDisplay, Position position);
};
ostream& operator<< (ostream& out, const Board& board);
#endif  // BOARD_H_
