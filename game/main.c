#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run() {
	char *t;
	registerBody("t1", newTextBox(5, 15, "We can barely fit anything in this thing!", 11, '*'));
	registerBody("t2", newTextBox(22, 10, "THAT'S WHAT SHE SAID", 1, '<'));
	registerBody("t3", newTextBox(30, 20, "Hey, Michael Scott is back!", 0, '='));
	registerBody("t4", newTextBox(40, 28, "feelings", -1, '#'));

	Body *r = newRectangle(20, 40, 20, 5, '*', 'l');
	Stroke *s = newStroke(1, newBorder("renatofag"));
	r->addStroke(r, s);
	registerBody("rect", r);

	Body *tb = newTextBox(55, 40, "BUT VARARGS ARE SO BEAUTIFUL!", 0, '!');
	tb->addStroke(tb, newStroke(1, newBorder("varargssuck")));
	registerBody("tb", tb);

	draw();

	gets(t);
	killByName("tb");
	draw();
}