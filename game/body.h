#ifndef BODY
#define BODY
#include <stdlib.h>

struct bodystruct {
	int x, y;
	void (*draw)(struct bodystruct *);
	int (*debug)();
};
typedef struct bodystruct Body;

LinkedList *bodies = NULL;

void paintRectangle(Body *self) {

}

void paintPoint(Body *self) {
	paint(self->x, self->y, '*');
}

void registerBody(Body *b) {
	if(!bodies) bodies = newList();
	bodies->add(bodies, b);
}

Body *newRectangle() {
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintRectangle;
	return b;
}

Body *newPoint(int x, int y) {
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintPoint;
	b->x = x;
	b->y = y;
	return b;
}

#endif
