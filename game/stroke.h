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
	char (*next)(Stroke*, int);
	char (*prev)(Stroke*, int);
	char (*exists)(Stroke*, int);
};

/* Cycles to the next Stroke border char */
char _border_next (Stroke *s, int side) {
	//Border *b = s->border[side>s->size-1?_STROKE_TOP:side];
	Border *b = s->border[side];
	int bIndex;
	if(!b) b = s->border[_STROKE_TOP];

	bIndex = ++b->index;
	if(bIndex>=b->size) bIndex = b->index = 0;

	return *(s->owner) = b->border[bIndex];
}

/* Cycles to the prev Stroke border char */
char _border_prev(Stroke *s, int side) {
	//Border *b = s->border[side>s->size-1?_STROKE_TOP:side];
	Border *b = s->border[side];
	int bIndex;
	if(!b) b = s->border[_STROKE_TOP];

	bIndex = --b->index;
	if(bIndex<0) bIndex = b->index = b->size-1;

	return *(s->owner) = b->border[bIndex];
}

/* Checks whether the Border exists in the given Stroke 
*  Returns 1 if Border exists.
*  Returns 0 if it does not exist.
*  Returns -1 if Stroke does not exist.
*/
char border_exists(Stroke *s, int side) {
	if(s==NULL) return -1;
	return s->border[side]!=NULL;
}

/* Creates a stroke from borders by cycling clockwise from the top */
Stroke *newStroke(int n, ...) {
	Stroke *s = (Stroke*)malloc(sizeof(Stroke));
	va_list args;
	int i;

	va_start(args, n);
	for(i=0;i<4;i++)
		if(i>n-1)
			s->border[i] = NULL;
		else
			s->border[i] = va_arg(args, Border*);
	va_end(args);

	s->next = _border_next;
	s->prev = _border_prev;
	s->exists = border_exists;
	s->index = 0;
	s->size = n;
	s->joint = '\0';

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