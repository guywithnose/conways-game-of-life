// Copyright 2015 Robert Bittle
#include <ncurses.h>
#include <iostream>

#include "./board.h"
#include "./cell.h"
#include "./cursesDisplay.h"

using std::cout;

void printValue(int x, int y);

int main() {
    Board* board = new Board();
    Board* newBoard;
    board->addCell(new Cell(Position(3, 3), true));
    board->addCell(new Cell(Position(4, 3), true));
    board->addCell(new Cell(Position(5, 3), true));
    board->addCell(new Cell(Position(5, 2), true));
    board->addCell(new Cell(Position(4, 1), true));
    CursesDisplay* display = new CursesDisplay();
    Position offset = Position(0, 0);
    board->display(display, offset);
    bool running = false;
    int ch = 0;
    while (ch != 'q') {
        refresh();
        ch = getch();
        clear();

        switch (ch) {
            case 114: // 'r'
            case 82: // 'R'
                timeout(60);
                running = true;
                break;
            case 115: // 's'
            case 83: // 'S'
                timeout(-1);
                running = false;
                newBoard = board->next();
                delete board;
                board = newBoard;
                board->display(display, offset);
                break;
            case 258:
            case 106:
                offset.y--;
                board->display(display, offset);
                break;
            case 259:
            case 107:
                offset.y++;
                board->display(display, offset);
                break;
            case 260:
            case 104:
                offset.x++;
                board->display(display, offset);
                break;
            case 261:
            case 108:
                offset.x--;
                board->display(display, offset);
                break;
        }

        if (running) {
            newBoard = board->next();
            delete board;
            board = newBoard;
            board->display(display, offset);
        }
    }

    clear();
    refresh();
    return 0;
}
