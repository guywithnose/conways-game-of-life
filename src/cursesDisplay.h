// Copyright 2015, Robert Bittle

#ifndef INCLUDE_CURSESDISPLAY_H_
#define INCLUDE_CURSESDISPLAY_H_

class CursesDisplay {
 public:
    CursesDisplay();
    ~CursesDisplay();
    void printCell(int x, int y);
};
#endif  // INCLUDE_CURSESDISPLAY_H_
