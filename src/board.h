// Copyright 2015 Robert Bittle(guywithnose@gmail.com)
#ifndef GAME_OF_LIFE_SRC_BOARD_H_
#define GAME_OF_LIFE_SRC_BOARD_H_
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

class Board {
 public:
     map<Position, Cell*, comparePositions> cells;
     Board* next();
     void addCell(Cell* cell);
     void feed(Position position);
     void wasAlive(Position position);
     void display(CursesDisplay* cursesDisplay, Position position);
};
ostream& operator<< (ostream& out, const Board& board);
#endif  // GAME_OF_LIFE_SRC_BOARD_H_
