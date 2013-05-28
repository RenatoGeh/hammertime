#ifndef BODY
#define BODY
#include <stdlib.h>

typedef struct bodystruct Body;

struct bodystruct {
	int x, y, w, h;
	char c,mode;
	void (*draw)(Body *);
	int (*debug)();
};

typedef struct {
	Body base;
	char *text;
}Text;

LinkedList *bodies = NULL;

void paintRectangle(Body *self) {
	int i, j, x = self->x, y = self->y;
	if(self->mode == 'f')                    // Modo Fill
		for(i = x; i < x + self->w ; i++)
			for(j = y; j < y + self->h; j++)
				paint(i,j,self->c);
	else                                 //Modo Line
		for(j = y; j < y + self->h; j++)
			if(j == y || j == (y + self->h - 1))  //Se for primeira ou ultima linha
				for(i = x; i < x + self->w ; i++)
					paint(i,j,self->c);
			else{
				paint(x,j,self->c);
				paint((x + self->w - 1),j,self->c);
			}

}
void paintCircle(Body *self) {
	int i, j, x = self->x, y = self->y,r = self->w;
	for(i = (x - r + 1); i < (x + r); i++)
		for (j = (y - r + 1); j < (y + r ); j++)
			if( ( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) < r*r)
				paint(i,j,self->c);
}
void paintPoint(Body *self) {
	paint(self->x, self->y, self->c);
}

void paintText(Body *self) {
	int i, j;
	char *t = ((Text*)self)->text;
	for(i = 0; i < self->h && *t; i++)
		for(j = 0; j < self->w && *t; j++)
			paint(self->x + j, self->y + i, *t++);
}

int registerBody(Body *b) {
	return bodies->add(bodies, b);
}

void killBody(Body *b) {
	Node *n = bodies->head;
	while(n) {
		if(n->value == b) {
			removeNode(n);
			break;
		}
		n = n->next;
	}
	free(b);
}

void initBodies() {
	bodies = newList();
}
Body *newPoint(int x, int y, char c) {
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintPoint;
	b->x = x;
	b->y = y;
	b->w = 1;
	b->h = 1;
	b->c = c;
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
	b->w = wrap? (wrap>0? min(strlen(text),wrap) : strlen(text)) : min(strlen(text), screen.width - x);
	b->h =  (strlen(text) + (b->w - 1)) / b->w; //rounding up
	return b;
}

Body *newRectangle(int x, int y, int h, int w, char c,char mode){
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintRectangle;
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->c = c;
	b->mode = mode;
	return b;
}
Body *newCircle(int x, int y, int r, char c){
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintCircle;
	b->x = x;
	b->y = y;
	b->w = r;
	b->h = b->w;
	b->c = c;
	return b;
}
#endif