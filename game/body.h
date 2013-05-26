#ifndef BODY
#define BODY
#include <stdlib.h>

typedef struct bodystruct Body;

struct bodystruct {
	int x, y, w, h;
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
	static int i, j;
	char *t = ((Text*)self)->text;
	for(i = 0; i < self->h && *t; i++)
		for(j = 0; j < self->w && *t; j++)
			paint(self->x + j, self->y + i, *t++);
}

void registerBody(Body *b) {
	if(!bodies) bodies = newList();
	bodies->add(bodies, b);
}

Body *newRectangle() {
	/*Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintRectangle;
	return b; TODO*/
}

Body *newPoint(int x, int y) {
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintPoint;
	b->x = x;
	b->y = y;
	b->w = 1;
	b->h = 1;
	return b;
}

Body *newText(int x, int y, char *text, int wrap) { //wrap = -1 -> never wrap, wrap = 0 -> wrap only on screen end, wrap>0 warp every wrap chars
	Text *t = (Text*) malloc(sizeof(Text));
	Body *b = NULL;
	t->text = text;
	b = (Body*) t;
	b->draw = paintText;
	b->x = x;
	b->y = y;
	b->w = wrap? (wrap>0? min(strlen(text),wrap) : strlen(text)) : min(strlen(text), WIDTH - x);
	b->h =  (strlen(text) + (b->w - 1)) / b->w; //rounding up
	fprintf(out, "%s: %d\t%d\n", text, b->w, b->h);
	return b;
}

#endif