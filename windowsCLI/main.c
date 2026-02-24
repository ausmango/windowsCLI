#include <stdio.h>
#include <curses.h>
#include "display.h"

int main() {

	initscr();
	batteryPercent();
	refresh();
	getch();
	endwin();
	
	return 0;
}
