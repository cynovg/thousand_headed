#include <stdio.h>
#include <curses.h>

int check_movement(int newx, int newy);

int main() {
    int ch, oldx, oldy;

    int x = oldx = 0;
    int y = oldy = 0;
    initscr();
    cbreak(); // disable buffering
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_LEFT:
                if (check_movement(x, y - 1)) {
                    oldy = y;
                    oldx = x;
                    y--;
                }
                break;
            case KEY_RIGHT:
                if (check_movement(x, y + 1)) {
                    oldy = y;
                    oldx = x;
                    y++;
                }
                break;
            case KEY_DOWN:
                if (check_movement(x + 1, y)) {
                    oldx = x;
                    oldy = y;
                    x++;
                }
                break;
            case KEY_UP:
                if (check_movement(x - 1, y)) {
                    oldx = x;
                    oldy = y;
                    x--;
                }
                break;
        }
        move(0, COLS-15);
        printw("OLD [%02d] [%03d]", oldx, oldy);
        move(1, COLS-15);
        printw("NEW [%02d] [%03d]", x, y);
        move(oldx, oldy);
        printw(" ");
        move(x, y);
        printw("o");
        refresh();
    }

    endwin();
    return 0;
}

int check_movement(int newx, int newy) {
    if (newx < 0 || newx > LINES - 1)
        return 0;
    if (newy < 0 || newy > COLS - 1)
        return 0;
    return 1;
}