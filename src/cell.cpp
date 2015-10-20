#include "./cell.h"

Position::Position() : x(0), y(0) {
}

Position::Position(int64_t x, int64_t y) {
    this->x = x;
    this->y = y;
}

Cell::Cell(Position position, bool wasAlive) {
    this->position = position;
    this->wasAlive = wasAlive;
    neighbors = 0;
}
