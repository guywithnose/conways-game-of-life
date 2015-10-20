#include "./board.h"

Board* Board::next() {
    Board* newBoard = new Board();

    map<Position, Cell*, comparePositions>::const_iterator it;
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

    for (it = newBoard->cells.begin(); it != newBoard->cells.end(); ++it) {
        if (it->second->neighbors < 2) {
            delete cells[it->first];
            newBoard->cells.erase(it->first);
        }

        if (it->second->neighbors > 3) {
            delete cells[it->first];
            newBoard->cells.erase(it->first);
        }

        if (it->second->neighbors == 2 && !it->second->wasAlive) {
            delete cells[it->first];
            newBoard->cells.erase(it->first);
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
    map<Position, Cell*, comparePositions>::const_iterator it;
    for (it = cells.begin(); it != cells.end(); ++it) {
        cursesDisplay->printCell(it->first.x + position.x, it->first.y + position.y);
    }
}

ostream& operator<<(ostream& out, const Board& board) {
    out << "START\n";
    map<Position, Cell*, comparePositions>::const_iterator it;
    for (it = board.cells.begin(); it != board.cells.end(); ++it) {
        out << it->first.x << "," << it->first.y << " => " << it->second->neighbors << '\n';
    }

    out << "END\n";
    return out;
}
