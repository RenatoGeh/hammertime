#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run() {
	char *t = (char*)malloc(sizeof(char));
	registerBody("t1", newTextBox(5, 15, "We can barely fit anything in this thing!", 11, '*'));
	registerBody("t2", newTextBox(22, 10, "THAT'S WHAT SHE SAID", 1, '<'));
	registerBody("t3", newTextBox(30, 20, "Hey, Michael Scott is back!", 0, '='));
	registerBody("t4", newTextBox(40, 28, "feelings", -1, '#'));

	Body *r = newRectangle(20, 40, 20, 5, '*', 'l');
	Stroke *s = newStroke(1, newBorder("renatolordofeverything"));
	r->addStroke(r, s);
	setStrokeJoint(s, 'X');
	registerBody("rect", r);

	Body *tb = newTextBox(55, 40, "VARARGS ARE SO BEAUTIFUL!", 0, '!');
	tb->addStroke(tb, newStroke(1, newBorder("varmyargs")));
	registerBody("tb", tb);

	Body *c = newCircle(60, 10, 5, '*', 'l');
	c->addStroke(c, newStroke(1, newBorder("!@#$^&*()")));
	registerBody("c", c);

	Body *huge = newRectangle(100, 10, 50, 40, '&', 'l');
	Stroke *leStroke = newStroke(4, newBorder(" THEY SEE ME STROKIN' "), 
		newBorder("nurses are not amused "), newBorder(" THEY HATIN' "), 
		newBorder("doctors be mad "));
	setStrokeJoint(leStroke, '$');
	huge->addStroke(huge, leStroke);
	registerBody("huge", huge);

	Body *line = newLine(1, 55, 150, 'h', '-');
	Stroke *lineStroke = newStroke(1, newBorder("-="));
	line->addStroke(line, lineStroke);
	setStrokeJoint(lineStroke, 'O');
	registerBody("line", line);

	draw();
	gets(t);
	killByName(t);
	draw();
}