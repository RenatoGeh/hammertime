#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>

int load() {
	char name[100];
	char hey[100] = "hey, ";
	Body *greeting;
	registerBody(newPoint(20,10,'-'));
	greeting = newText(10,12,"hey, dude.", 14);
	registerBody(greeting);
	registerBody(newText(screen.width - 13, 4, "Automatic wrapping like a boss.", 0));
	registerBody(newText(screen.width - 13, screen.height - 3, "But that's optional.", -1));
	registerBody(newRectangle(0,0,1,5,'*','f'));
	registerBody(newRectangle(10,0,4,4,'=','l'));
	draw();
	printf("Write your name >:");
	gets(name);
	killBody(greeting);
	registerBody(newText(10, 12, strcat(strcat(hey , name), "."), 30));
	draw();
}