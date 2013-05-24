#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
//#include <sys/ioctl.h>


//struct winsize ws;

void load() {
	//ioctl(0, TIOCGWINSZ, &ws);
	//printf("%d\t%d", ws.ws_col, ws.ws_row);
	registerBody(newPoint(10,10));
}

void update(int dt) {
	
}