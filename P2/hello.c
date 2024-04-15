#include <ncurses.h>

int main(){
    initscr();
    printw("Hello World, estoy usando una ventana");
    refresh();
    getch();
    endwin();

    return 0;
}