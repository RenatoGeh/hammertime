#ifndef BODY
#define BODY
#include <stdlib.h>

struct bodystruct {
	int x, y;
	void (*draw)();
};
typedef struct bodystruct Body;

void paintRectangle() {
	printf("I'm a rectangle!\n");
}

Body *newRectangle() {
	Body *b = malloc(sizeof(Body));
	b->draw = paintRectangle;
	return b;
}

#endif