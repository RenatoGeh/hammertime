#ifndef STROKE
#define STROKE

#include <stdarg.h>

#define _STROKE_TOP 0
#define _STROKE_RIGHT 1
#define _STROKE_BOTTOM 2
#define _STROKE_LEFT 3

typedef struct {
	int size;
	int index;
	char *border;
} Border;

typedef struct strokestruct Stroke;
struct strokestruct {
	/* Cyclical sequence of border chars */
	Border* border[4];
	int size;
	int index;
	char *owner;
	char joint;
	void (*next)(Stroke*);
	void (*prev)(Stroke*);
};

/* Cycles to the next Stroke border char */
void _border_next (Stroke *s) {
	int side = 0;
	Border *b = s->border[side];
	int bIndex = b->index;

	bIndex = ++b->index;
	if(bIndex>=b->size) bIndex = b->index = 0;

	*(s->owner) = b->border[bIndex];
}

/* Cycles to the prev Stroke border char */
void _border_prev(Stroke *s) {
	int side = 0;
	Border *b = s->border[side];
	int bIndex = b->index;

	bIndex = --b->index;
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

void setStrokeJoint(Stroke *s, char joint) {
	s->joint = joint;
}

/* Creates a new side-border with the given chars */
Border *newBorder(char *str) {
	Border *b = (Border*) malloc(sizeof(Border));

	b->size = strlen(str);
	b->index = 0;
	b->border = str;

	return b;
}

#endif