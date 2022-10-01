#include <curses.h>
#include <stdlib.h>

#define MAXLINES 100
#define MAXCOLS 300

int check_movement(int newx, int newy);
void generate_maze(int maxlines, int cols);
void show_maze(int maxlines, int cols);
static int maze[MAXLINES][MAXCOLS   ];

int main() {
    int ch, oldx, oldy;

    int x = oldx = 0;
    int y = oldy = 0;
    initscr();
    cbreak(); // disable buffering
    keypad(stdscr, TRUE);
    noecho();
    generate_maze(LINES, COLS);
    show_maze(LINES, COLS);
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
        show_maze(LINES, COLS);
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
    if (maze[newx][newy] == 1)
        return 0;
    if (newx < 0 || newx > LINES - 1)
        return 0;
    if (newy < 0 || newy > COLS - 1)
        return 0;
    return 1;
}

void generate_maze(int maxlines, int maxcols) {
    for (int x = 1; x < maxlines; x += 3) {
        for (int y = 1; y < maxcols; y += 2)
            maze[x][y] = rand() % 2 ? 1 : 0;
    }
}

void show_maze(int maxlines, int maxcols) {
    for (int x = 0; x < maxlines; x++) {
        for (int y = 0; y < maxcols; y++ )
            if (maze[x][y] == 1) {
                move(x, y);
                printw("X");
            }
    }
}