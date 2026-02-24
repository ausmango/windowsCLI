#include <stdio.h>
#include "ram.h"
#include "battery.h"
#include <curses.h>

int main() {

	initscr();

	printw(acLine());

	
	return 0;
}
