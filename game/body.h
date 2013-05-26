#ifndef BODY
#define BODY
#include <stdlib.h>

typedef struct bodystruct Body;

struct bodystruct {
	int x, y;
	void (*draw)(Body *);
	int (*debug)();
};

typedef struct {
	Body base;
	char *text;
}Text;

LinkedList *bodies = NULL;

void paintRectangle(Body *self) {

}

void paintPoint(Body *self) {
	paint(self->x, self->y, '*');
}

void paintText(Body *self) {
	int a = self->x;
	char *t = ((Text*)self)->text;
	while(*t) 
		paint(a++, self->y, *t++);
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

Body *newText(int x, int y, char *text) {
	Text *t = (Text*) malloc(sizeof(Text));
	Body *b = NULL;
	t->text = text;
	b = (Body*) t;
	b->draw = paintText;
	b->x = x;
	b->y = y;
	return b;
}

#endif