#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run() {
	char *str = (char*)malloc(100*sizeof(char));
	Polynomial *poly;

	registerBody("x-axis", newLine(0, screen.height/2, screen.width, 'h', '-'));
	registerBody("y-axis", newLine(screen.width/2, 0, screen.height, 'v', '|'));
	registerBody("Poly", newPolynomial(0, 0, -1, -1, '*', 1, 1, -screen.width/2));

	poly = (Polynomial*)getByName("Poly");
	poly->toString(str, poly);

	registerBody("xlabel", newText(0, screen.height/2-1, "x-axis", 0));
	registerBody("ylabel", newText(screen.width/2+1, 0, "y-axis", 1));

	draw();

	puts("Poly:");
	puts(str);
	/*char *t = (char*)malloc(sizeof(char));
	registerBody("t1", newTextBox(50, 15, "STOP", 11, '*'));
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
	killByName(t);*/

	/*Body *t = newTable(0, 0, 5, 5, -25, -12, '!', '=');
	Stroke *s = newStroke(4, newBorder("-"), newBorder("|"), newBorder("-"), newBorder("|"));
	t->addStroke(t, s);
	setStrokeJoint(s, 'O');

	Table *tab = (Table*)t;
	Body *c = newCircle(0, 0, 4, '*', 'l');
	c->addStroke(c, newStroke(1, newBorder("!@#$^&*()-+")));
	tab->add(tab, c, 1, 1, 1);

	Body *rect = newRectangle(0, 0, 15, 8, '@', 'f');
	Stroke *rectStroke = newStroke(4, newBorder("wassup"), newBorder("dawgs"),
		newBorder("chillin'"), newBorder("much?"));
	setStrokeJoint(rectStroke, '+');
	rect->addStroke(rect, rectStroke);
	tab->add(tab, rect, 3, 3, 1);

	Body *tb = newTextBox(1, 2, " Table is so awesome! Said everyone. ", 21, '=');
	Stroke *tbStroke = newStroke(4, newBorder("amazing"), newBorder("genius"),
		newBorder("10/10_reviews_"), newBorder("WOOHO!"));
	tb->addStroke(tb, tbStroke);
	tab->add(tab, tb, 2, 4, 1);

	registerBody("t", t);
	draw();*/
}