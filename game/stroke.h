#ifndef STROKE
#define STROKE

#include <stdlib.h>
#include <stdarg.h>
#define BORDER_MAX 10

typedef struct {
	/* Cyclical sequence of border chars */
	Border* border[4];
	void (*next)(Stroke*);
	void (*prev)(Stroke*);
} Stroke;

typedef struct {
	int size;
	char border[BORDER_MAX];
} Border;

/* Gets the next Stroke border char */
void _border_next (Stroke *s) {

}

/* Gets the prev Stroke border char */
void _border_prev(Stroke *s) {

}

/* Creates a stroke from borders by cycling clockwise from the top */
Stroke *newStroke(int n, ...) {
	Stroke *s = (Stroke*)malloc(sizeof(Stroke));
	va_list args;
	int i;

	va_start(args, n);
	for(i=0;i<4;i++) {
		if(i>n)
			s->border[i] = NULL;
		else
			s->border[i] = va_arg(args, Border*);
	}
}

/* Creates a new side-border with the given chars */
Border *newBorder(int n, ...) {
	Border *b = (Border*)malloc(sizeof(Border));
	va_list args;
	int i;

	va_start(args, n);
	b->size = n;
	for(i=0;i<n;i++)
		b->border[i] = va_arg(args, char);

	return b;
}

#endif