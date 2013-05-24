#ifndef BODY
#define BODY
#include <stdlib.h>

struct bodystruct {
	int x, y;
	void (*draw)();
};
typedef struct bodystruct body;

void paintRectangle() {
	printf("I'm a rectangle!\n");
}

body *newRectangle() {
	body *b = malloc(sizeof(body));
	b->draw = paintRectangle;
	return b;
}

#endif