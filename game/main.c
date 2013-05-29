#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run() {
	/*char name[100];
	Body *greeting, *box;
	greeting = newText(15, 12, "dude", -1);
	registerBody(newText(10, 12, "hey, ", -1));
	registerBody(greeting);
	registerBody(box=newRectangle(9, 11, 3, 11, '-', 'l'));
	draw();
	printf("Write your name >:");
	gets(name);
	killBody(greeting);
	registerBody(newText(15, 12, name, -1));*/
	registerBody(newTextBox(5, 15, "We can barely fit anything in this thing!", 11, '*'));
	registerBody(newTextBox(22, 10, "THAT'S WHAT SHE SAID", 1, '<'));
	registerBody(newTextBox(30, 20, "Hey, Michael Scott is back!", 0, '='));
	registerBody(newTextBox(40, 28, "feelings", -1, '#'));
	draw();
}