#ifndef BODY
#define BODY
#include <stdlib.h>

struct bodystruct {
	int x, y;
	void (*draw)(struct bodystruct *, char[HEIGHT][WIDTH+1]);
	int (*debug)();
};
typedef struct bodystruct Body;

Body* bodies[1000];
int bsize = 0;

void paintRectangle(Body *self, char terminal[HEIGHT][WIDTH+1]) {

}

void paintPoint(Body *self, char terminal[HEIGHT][WIDTH+1]) {
	paint(self->x, self->y, '*');
}

void registerBody(Body *b) {
	bodies[bsize++] = b;
}

Body *newRectangle() {
	Body *b = malloc(sizeof(Body));
	b->draw = paintRectangle;
	return b;
}

Body *newPoint(int x, int y) {
	Body *b = malloc(sizeof(Body));
	b->draw = paintPoint;
	b->x = x;
	b->y = y;
	return b;
}

#endif
