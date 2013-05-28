#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>

int run() {
	char name[100];
	Body *greeting;
	greeting = newText(15, 12, "dude", -1);
	registerBody(newText(10, 12, "hey, ", -1));
	registerBody(greeting);
	registerBody(newRectangle(9, 11, 3, 11, '-', 'l'));
	draw();
	printf("Write your name >:");
	gets(name);
	killBody(greeting);
	registerBody(newText(15, 12, name, -1));
	draw();
}