// Copyright 2015, Robert Bittle

#ifndef CURSESDISPLAY_H_
#define CURSESDISPLAY_H_

class CursesDisplay {
 public:
    CursesDisplay();
    ~CursesDisplay();
    void printCell(int x, int y);
};
#endif  // CURSESDISPLAY_H_
