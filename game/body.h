#ifndef BODY
#define BODY
#include <stdlib.h>

typedef struct bodystruct Body;

struct bodystruct {
	int x, y, w, h;
	char c, mode;
	void (*draw)(Body *);
};

typedef struct {
	Body base;
	char *text;
} Text;

LinkedList *bodies = NULL;

void paintRectangle(Body *self) {
	int i, j, x = self->x, y = self->y;
	int w=self->w, h=self->h;
	if(self->mode == 'f')                    // Modo Fill
		for(i = x;i < x + w; i++)
			for(j = y; j < y + h; j++)
				paint(i,j,self->c);
	else                                 //Modo Line
		for(j = y; j < y + h; j++)
			if(j == y || j == (y + h - 1))  //Se for primeira ou ultima linha
				for(i = x; i < x + w ; i++)
					paint(i,j,self->c);
			else {
				paint(x,j,self->c);
				paint((x + w - 1),j,self->c);
			}
}

void paintCircle(Body *self) {
	int i, j, x = self->x, y = self->y, r = self->w - 1;
	if(self->mode == 'f'){
		for(i = x - r; i <= x + r; i++)
			for (j = y - r; j <= y + r; j++)
				if( ( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) <= r*r)
					paint(i,j,self->c);
	}
	else
		for(i = x - r; i <= x + r; i++)
			for (j = y - r; j <= y + r; j++)
				if( (( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) >= r*r-2) && (( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) <= r*r))
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

void paintTextBox(Body *self) {
	self->w+=2;
	self->h+=2;
	self->x--;
	self->y--;
	paintRectangle(self);
	self->w-=2;
	self->h-=2;
	self->x++;
	self->y++;
	paintText(self);
}

void clearBody(Body *b) {
	free(b);
}

int registerBody(Body *b) {
	return bodies->add(bodies, b);
}

void killBody(Body *b) {
	Node *n = bodies->head;
	while(n) {
		if(n->value == b) {
			if(n==bodies->tail) bodies->tail = n->prev;
			if(n==bodies->head) bodies->head = n->next;
			removeNode(n);
			bodies->size--;
			break;
		}
		n = n->next;
	}
	clearBody(b);
}

void clearBodies() {
	Node *n = bodies->head;
	bodies->head = NULL;
	bodies->tail = NULL;
	if(!n) return;
	while(n->next) {
		clearBody(removeNode(n->next));
	}

	clearBody(removeNode(n));
	bodies->size = 0;
}

void paintLine(Body *self) {
	int i;
	if(self->h == 0) //vertical
		for(i = 0; i < self->w; i++)
			paint(self->x + i, self->y, self->c);
	else		//horizontal
		for(i = 0; i < self->h; i++)
			paint(self->x, self->y + i, self->c);
}

void initBodies() {
	bodies = newList();
}

Body *newPoint(int x, int y, char c) {
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintPoint;
	b->x = x;
	b->y = y;
	b->w = b->h = 1;
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

Body *newCircle(int x, int y, int r, char c, char mode){
	Body *b = (Body*) malloc(sizeof(Body));
	b->draw = paintCircle;
	b->x = x;
	b->y = y;
	b->h = b->w = r;
	b->c = c;
	b->mode = mode;
	return b;
}

Body *newLine(int x, int y, int size, char dir, char c) {
	Body *b = (Body*) malloc(sizeof(Body));
	b->x = x;
	b->y = y;
	if(dir=='h') {
		b->w = size;
		b->h = 0;
	} else {
		b->h = size;
		b->w = 0;
	}
	b->c = c;
	b->draw = paintLine;
	return b;
}

Body *newTextBox(int x, int y, char *text, int wrap, char c) {
	Text *t = (Text*)malloc(sizeof(Text));
	Body *b = (Body*)malloc(sizeof(Body));

	t->text = text;
	b = (Body*)t;
	b->x = x;
	b->y = y;
	b->w = wrap?(wrap>0?min(strlen(text), wrap):strlen(text)):min(strlen(text), screen.width-x);
	b->h = (strlen(text)+(b->w-1))/b->w;
	b->mode='l';
	b->c = c;
	b->draw = paintTextBox;

	return b;
}

#endif