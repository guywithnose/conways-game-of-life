// Copyright 2015, Robert Bittle

#include "./cursesDisplay.h"

#include <math.h>
#include <ncurses.h>
#include <string.h>

CursesDisplay::CursesDisplay() {
    initscr();
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_RED);
    init_pair(8, COLOR_WHITE, COLOR_GREEN);
    init_pair(9, COLOR_WHITE, COLOR_YELLOW);
    init_pair(10, COLOR_WHITE, COLOR_CYAN);
    init_pair(11, COLOR_WHITE, COLOR_BLUE);
    init_pair(12, COLOR_WHITE, COLOR_MAGENTA);
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}

CursesDisplay::~CursesDisplay() {
    endwin();
}

void CursesDisplay::printCell(int x, int y) {
    if (x > 0 && y > 0 && x < COLS && y < LINES) {
        move(y, x);
        printw("O");
    }
}

