#include "hammertime.h"
#include <string.h>

/** Hammertime Showcase:
 *    Hilbert Curves
 *
 *  @author Renato Lui Geh
 *
 *  An example application on how Hammertime can be used
 *  in a Computer Science class. The display of the 
 *  Hilbert Curves can be show-cased in classes.
 *  
 *  This example also reveals how simple Hammertime can
 *  be. By simplifying the graphical instructions, the
 *  developer can focus on the theory and actual algorithm
 *  procedures instead.
 *
 *  Plus we like to show-off our work.
 *  It boosts our fragile self-esteems.
 *  
 *  This example may be used and copied as you like. However,
 *  if you do use and copy this source code, you are bound by
 *  this license to go to the busiest, crowdest place in your
 *  surroundings and scream:
 *
 *  "HAMMERTIME AT www.github.com/RenatoGeh/Hammertime IS THE 
 *   AWESOMEST GRAPHICS FRAMEWORK OF ALL TIME"
 *
 *  We do not take responsability over any kind of aggression,
 *  be it physical or moral, or any and all damage the screamer
 *  may end up enduring during this awesome moment of his/her life.
*/

typedef enum {RIGHT, LEFT, UP, DOWN} Direction;
typedef enum {A, B, C, D} Type;

void drawLine(int* x, int* y, Direction dir, int width) {
	int sX, sY;
	char d = (dir==RIGHT||dir==LEFT)?'h':'v';

	if(dir==LEFT)
		(*x) -= width;
	else if(dir==UP)
		(*y) -= width;

	registerBody(NULL, newLine(*x, *y, width, d, '#'));

	if(dir==RIGHT)
		(*x) += width;
	else if(dir==DOWN)
		(*y) += width;
}

void hilbert(int k, int* x, int* y, int width, Type t) {
	if(k<1) return;

	if(t==A) {
		hilbert(k-1, x, y, width, D);
		drawLine(x, y, LEFT, width);
		hilbert(k-1, x, y, width, A);
		drawLine(x, y, DOWN, width);
		hilbert(k-1, x, y, width, A);
		drawLine(x, y, RIGHT, width);
		hilbert(k-1, x, y, width, B);
	} else if(t==B) {
		hilbert(k-1, x, y, width, C);
		drawLine(x, y, UP, width);
		hilbert(k-1, x, y, width, B);
		drawLine(x, y, RIGHT, width);
		hilbert(k-1, x, y, width, B);
		drawLine(x, y, DOWN, width);
		hilbert(k-1, x, y, width, A);
	} else if(t==C) {
		hilbert(k-1, x, y, width, B);
		drawLine(x, y, RIGHT, width);
		hilbert(k-1, x, y, width, C);
		drawLine(x, y, UP, width);
		hilbert(k-1, x, y, width, C);
		drawLine(x, y, LEFT, width);
		hilbert(k-1, x, y, width, D);
	} else {
		hilbert(k-1, x, y, width, A);
		drawLine(x, y, DOWN, width);
		hilbert(k-1, x, y, width, D);
		drawLine(x, y, LEFT, width);
		hilbert(k-1, x, y, width, D);
		drawLine(x, y, UP, width);
		hilbert(k-1, x, y, width, C);
	}
}

int run(int argc, char* args[]) {
	int x, y;
	int n=5;

	if(argc > 1)
		n = atol(args[1]);

	x = screen.width-5;
	y = 5;

	hilbert(n, &x, &y, 5, A);
	draw();

	return 0;
}