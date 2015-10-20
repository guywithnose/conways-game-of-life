// Copyright 2015 Robert Bittle
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>

#include "./board.h"
#include "./cell.h"
#include "./cursesDisplay.h"

using std::cin;
using std::cout;
using std::ifstream;

void printValue(int x, int y);

int main(int argc, char** argv) {
    Board* board = new Board();
    Board* newBoard;

    int64_t x;
    int64_t y;
    if (argc == 2) {
        ifstream inputFile;
        inputFile.open(argv[1]);
        while (inputFile) {
            inputFile >> x;
            if (inputFile) {
                inputFile >> y;
                board->addCell(new Cell(Position(x, y), true));
            }
        }
    } else {
        unsigned int seed = time(NULL);
        for (int i = 0; i < 5000; i++) {
            x = rand_r(&seed) % 100;
            y = rand_r(&seed) % 100;
            Position p = Position(x, y);
            if (board->cells.find(p) == board->cells.end()) {
                board->addCell(new Cell(p, true));
            }
        }
    }

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
            case 114:  // 'r'
            case 82:  // 'R'
                timeout(60);
                running = true;
                break;
            case 115:  // 's'
            case 83:  // 'S'
                timeout(-1);
                running = false;
                newBoard = board->next();
                delete board;
                board = newBoard;
                break;
            case 258:  // Down
                offset.y--;
                break;
            case 106:  // 'j'
                offset.y -= 10;
                break;
            case 74:  // 'J'
                offset.y -= 25;
                break;
            case 10:  // '^J'
                offset.y -= 100;
                break;
            case 259:  // Up
                offset.y++;
                break;
            case 107:  // 'k'
                offset.y += 10;
                break;
            case 75:  // 'K'
                offset.y += 25;
                break;
            case 11:  // '^K'
                offset.y += 100;
                break;
            case 260:  // Left
                offset.x++;
                break;
            case 104:  // 'h'
                offset.x += 10;
                break;
            case 72:  // 'H'
                offset.x += 25;
                break;
            case 8:  // '^H'
                offset.x += 100;
                break;
            case 261:  // Right
                offset.x--;
                break;
            case 108:  // 'l'
                offset.x -= 10;
                break;
            case 76:  // 'L'
                offset.x -= 25;
                break;
            case 12:  // '^L'
                offset.x -= 100;
                break;
        }

        if (running) {
            newBoard = board->next();
            delete board;
            board = newBoard;
        }

        board->display(display, offset);
    }

    clear();
    refresh();
    return 0;
}
