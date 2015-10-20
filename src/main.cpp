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
    board->addCell(new Cell(Position(3, 3), true));
    board->addCell(new Cell(Position(4, 3), true));
    board->addCell(new Cell(Position(5, 3), true));
    board->addCell(new Cell(Position(5, 4), true));
    CursesDisplay* display = new CursesDisplay();
    board->display(display);
    bool running = false;
    int ch = 0;
    while (ch != 'q') {
        refresh();
        ch = getch();
        clear();

        switch (ch) {
            // R -> Run
            case 114:
            case 82:
                timeout(60);
                running = true;
                break;
            // S -> Step
            case 115:
            case 83:
                timeout(-1);
                running = false;
                Board* newBoard = board->next();
                delete board;
                board = newBoard;
                board->display(display);
                break;
        }

        if (running) {
            Board* newBoard = board->next();
            delete board;
            board = newBoard;
            board->display(display);
        }
    }

    clear();
    refresh();
    return 0;
}
