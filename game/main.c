#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795L
#define EULER 2.7182818284590452353602874713527L

double absolute(double n) {return n<0?-n:n;}
double exp2(double k) {
	double p;
	for(p=1;k>0;k--,p*=2);
	return p;
}
double eulerx(double k) {
	double p;
	for(p=1;k>0;k--,p*=EULER);
	return p/10;
}
double signx(double x) {return x>0?25:x<0?-25:0;}
double ln(double n) {return 10*log(n);}
double logarithm10(double n) {return 10*log10(n);}
double sinx(double x) {return 50*sin(x/10);}
double sinix(double x) {return 50*sin(100/x);}
double cosx(double x) {return 50*cos(x/10);}
double tanx(double x) {return 5*tan(x/10);}
double poly2(double x) {return x*x/20;}
double invx(double x) {return 250/x;}
double arcsin(double x) {return 20*asin(x/20);}
double arccos(double x) {return 20*acos(x/20);}
double arctan(double x) {return 20*atan(x/20);}

double f(double x) {
	x/=10;
	return (x*x*x + 5*x*x + 6*x)/(1-x*x);
}

int run() {
	char *str = (char*)malloc(100*sizeof(char));
	//Polynomial *poly;

	function.addAxis();
	//registerBody("Poly", newPolynomial(-1, -1, -1, -1, '*', 2, 1, 0, 0));
	//registerBody("First", newPolynomial(-1, -1, -1, -1, 'o', 1, 1, 0));
	//registerBody("Third", newPolynomial(-1, -1, -1, -1, '+', 3, 1, 8, 10, 0));
	//registerBody("Sin", newFunction(-1, -1, -1, -1, '#', sinx));
	//registerBody("Cos", newFunction(-1, -1, -1, -1, '!', cosx));
	//registerBody("Tan", newFunction(-1, -1, -1, -1, '$', tanx));
	//registerBody("Abs", newFunction(-1, -1, -1, -1, '&', absolute));
	//registerBody("exp2", newFunction(-1, -1, -1, -1, 'o', exp2));
	//registerBody("ln", newFunction(-1, -1, -1, -1, '+', ln));
	//registerBody("log10", newFunction(-1, -1, -1, -1, '=', logarithm10));
	//registerBody("e^x", newFunction(-1, -1, -1, -1, 'e', eulerx));
	//registerBody("signum", newFunction(-1, -1, -1, -1, 's', signx));
	//registerBody("sqrt", newFunction(-1, -1, -1, -1, '@', sqrt));
	//registerBody("Poly2", newFunction(-1, -1, -1, -1, '~', poly2));
	registerBody("sin(1/x)", newFunction(-1, -1, -1, -1, 'x', sinix));
	//registerBody("1/x", newFunction(-1, -1, -1, -1, '|', invx));
	//registerBody("arcsin(x)", newFunction(-1, -1, -1, -1, '?', arcsin));
	//registerBody("arccos(x)", newFunction(-1, -1, -1, -1, '?', arccos));
	//registerBody("arctan(x)", newFunction(-1, -1, -1, -1, '?', arctan));
	//registerBody("f(x)", newFunction(-1, -1, -1, -1, 'f', f));


	//poly = (Polynomial*)getByName("Poly");
	//poly->toString(str, poly);

	draw();

	//puts("Poly:");
	//puts(str);
	//free(str);

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