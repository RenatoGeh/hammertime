#ifndef STROKE
#define STROKE

#include <stdlib.h>
#include <stdarg.h>
#define BORDER_MAX 10

typedef struct {
	int size;
	int index;
	char border[BORDER_MAX];
} Border;

typedef struct strokestruct Stroke;
struct strokestruct {
	/* Cyclical sequence of border chars */
	Border* border[4];
	int size;
	int index;
	char *owner;
	void (*next)(Stroke*);
	void (*prev)(Stroke*);
};

/* Cycles to the next Stroke border char */
void _border_next (Stroke *s) {
	int sIndex;
	int bIndex;
	Border *b;

	//sIndex = s->index;
	//if(border[sIndex]->index>border[sIndex]->size) s->index++;
	sIndex = s->index;

	if(sIndex>=s->size) sIndex = s->index = 0;
	b = s->border[sIndex];

	b->index++;

	bIndex = b->index;
	if(bIndex>=b->size) bIndex = b->index = 0;

	*(s->owner) = b->border[bIndex];
}

/* Cycles to the prev Stroke border char */
void _border_prev(Stroke *s) {
	int sIndex;
	int bIndex;
	Border *b;

	//if(border[sIndex]->index<0) s->index--;
	//s->index--;
	b->index--;
	sIndex = s->index;

	if(sIndex<0) sIndex = s->index = s->size-1;
	b = s->border[sIndex];

	bIndex = b->index;
	if(bIndex<0) bIndex = b->index = b->size-1;

	*(s->owner) = b->border[bIndex];
}

/* Creates a stroke from borders by cycling clockwise from the top */
Stroke *newStroke(int n, ...) {
	Stroke *s = (Stroke*)malloc(sizeof(Stroke));
	va_list args;
	int i;

	va_start(args, n);
	for(i=0;i<4;i++)
		if(i>n)
			s->border[i] = NULL;
		else
			s->border[i] = va_arg(args, Border*);
	va_end(args);

	s->next = _border_next;
	s->prev = _border_prev;
	s->index = 0;
	s->size = n;

	return s;
}

/* Creates a new side-border with the given chars */
Border *newBorder(int n, ...) {
	Border *b = (Border*)malloc(sizeof(Border));
	va_list args;
	int i;

	va_start(args, n);
	b->size = n;
	b->index = 0;
	for(i=0;i<n;i++)
		b->border[i] = va_arg(args, int);
	va_end(args);

	return b;
}

#endif