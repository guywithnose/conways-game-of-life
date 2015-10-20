// Copyright 2015 Robert Bittle
#include "./board.h"

#include <utility>

Board* Board::next() {
    Board* newBoard = new Board();

    cellMap::const_iterator it;
    for (it = cells.begin(); it != cells.end(); ++it) {
        newBoard->wasAlive(it->first);
        newBoard->feed(Position(it->first.x - 1, it->first.y - 1));
        newBoard->feed(Position(it->first.x - 1, it->first.y));
        newBoard->feed(Position(it->first.x - 1, it->first.y + 1));
        newBoard->feed(Position(it->first.x, it->first.y - 1));
        newBoard->feed(Position(it->first.x, it->first.y + 1));
        newBoard->feed(Position(it->first.x + 1, it->first.y - 1));
        newBoard->feed(Position(it->first.x + 1, it->first.y));
        newBoard->feed(Position(it->first.x + 1, it->first.y + 1));
    }

    it = newBoard->cells.begin();
    while (it != newBoard->cells.end()) {
        cellMap::const_iterator toErase = it;
        ++it;
        if (toErase->second->neighbors < 2 ||
                toErase->second->neighbors > 3 ||
                (toErase->second->neighbors == 2 && !toErase->second->wasAlive)
           ) {
            delete cells[toErase->first];
            newBoard->cells.erase(toErase);
        }
    }

    return newBoard;
}

void Board::feed(Position position) {
    if (cells.find(position) == cells.end()) {
        this->addCell(new Cell(position, false));
    }

    cells[position]->neighbors++;
}

void Board::wasAlive(Position position) {
    if (cells.find(position) == cells.end()) {
        this->addCell(new Cell(position, true));
    } else {
        cells[position]->wasAlive = true;
    }
}

void Board::addCell(Cell* cell) {
    if (cells.find(cell->position) != cells.end()) {
        throw "Cell already exists";
    }

    cells.insert(std::pair<Position, Cell*>(cell->position, cell));
}

void Board::display(CursesDisplay* cursesDisplay, Position position) {
    cellMap::const_iterator it;
    for (it = cells.begin(); it != cells.end(); ++it) {
        cursesDisplay->printCell(
            it->first.x + position.x,
            it->first.y + position.y);
    }
}

ostream& operator<<(ostream& out, const Board& board) {
    out << "START\n";
    cellMap::const_iterator it;
    for (it = board.cells.begin(); it != board.cells.end(); ++it) {
        out << it->first.x << "," << it->first.y << " => "
            << it->second->neighbors << '\n';
    }

    out << "END\n";
    return out;
}
