#include <ncursesw/ncurses.h>

int main(){
	initscr();
	printw("Hello, world\n");
	refresh();
	getch();
	endwin();
	// ytytgfdf
	return 0;
}
