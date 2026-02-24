#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "battery.h"
#include "ram.h"

void displayRam() {

}

void batteryPercent() {
	int percent = getBatteryPercent();
	mvprintw(0, 0, "Battery: %d%", percent);


}

void acLine() {

}

void batteryTime() {

}