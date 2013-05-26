#include "hammertime.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
//#include <sys/ioctl.h>

//struct winsize ws;

void load() {
	//ioctl(0, TIOCGWINSZ, &ws);
	//printf("%d\t%d", ws.ws_col, ws.ws_row);
	//registerBody(newPoint(10,10));

	register int i;
	LinkedList *list = newList();
	Body *b[5];

	for(i=0;i<5;i++) {
		b[i] = newRectangle();
		list->add(list, b[i]);
		printf("L'Original: [%d]=%p\n", i, b[i]);
	}

	for(i=0;i<5;i++) printf("TEEHEE: [%d]=%p\n", i, list->get(list, i));

	printf("[%d, %d]\n", getConsoleWidth(), getConsoleHeight());
}

void update(int dt) {
	
}
