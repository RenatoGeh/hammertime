#ifndef BODY
#define BODY

#include <stdlib.h>
#include "stroke.h"

typedef struct bodystruct Body;

struct bodystruct {
	int x, y, w, h;
	char c, mode, *name;
	Stroke *stroke;
	void (*draw)(Body *);
	void (*addStroke)(Body*, Stroke *s);
};

typedef struct {
	Body base;
	char *text;
} Text;

LinkedList *bodies = NULL;

void _body_addStroke(Body *b, Stroke *s) {
	b->stroke = s;
	s->owner = &(b->c);
	s->next(s);
	s->prev(s);
}

void paintRectangle(Body *self) {
	int i, j, x = self->x, y = self->y;
	int w=self->w, h=self->h;
	Stroke *s = self->stroke;
	if(self->mode == 'f')                    // Modo Fill
		for(i = x;i < x + w; i++)
			for(j = y; j < y + h; j++) {
				paint(i,j,self->c);
				if(s!=NULL) s->next(s);
			}
	else                                 //Modo Line
		for(j = y; j < y + h; j++)
			if(j == y || j == (y + h - 1))  //Se for primeira ou ultima linha
				for(i = x; i < x + w ; i++) {
					paint(i,j,self->c);
					if(s!=NULL) s->next(s);
				}
			else {
				paint(x,j,self->c);
				if(s!=NULL) s->next(s);
				paint((x + w - 1),j,self->c);
				if(s!=NULL) s->next(s);
			}
}

void paintCircle(Body *self) {
	int i, j, x = self->x, y = self->y, r = self->w - 1;
	Stroke *s = self->stroke;
	if(self->mode == 'f'){
		for(i = x - r; i <= x + r; i++)
			for (j = y - r; j <= y + r; j++)
				if( ( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) <= r*r) {
					paint(i,j,self->c);
					if(s!=NULL) s->next(s);
				}
	}
	else
		for(i = x - r; i <= x + r; i++)
			for (j = y - r; j <= y + r; j++)
				if( (( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) >= r*r-2) && (( (i-x) * (i-x) ) + ( (j-y) * (j-y) ) <= r*r)) {
					paint(i,j,self->c);
					if(s!=NULL) s->next(s);
				}
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

int registerBody(char *name, Body *b) {
	b->name = name;
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

void killByName(char *name) {
	Node *n = bodies->head;
	while(n) {
		if(strcmp(name, ((Body*)n->value)->name) == 0) {
			if(n==bodies->tail) bodies->tail = n->prev;
			if(n==bodies->head) bodies->head = n->next;
			clearBody(removeNode(n));
			bodies->size--;
			break;
		}
		n = n->next;
	}
}

Body *getByName(char *name) {
	Node *n = bodies->head;
	while(n) {
		if(strcmp(name, ((Body*)n->value)->name) == 0)
			return n->value;
		n = n->next;
	}
	return NULL;
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
	Stroke *s = self->stroke;
	if(self->h == 0) //vertical
		for(i = 0; i < self->w; i++) {
			paint(self->x + i, self->y, self->c);
			if(s!=NULL) s->next(s);
		}
	else		//horizontal
		for(i = 0; i < self->h; i++) {
			paint(self->x, self->y + i, self->c);
			if(s!=NULL) s->next(s);
		}
}

void initBodies() {
	bodies = newList();
}

Body *_defBody(int x, int y, int w, int h, char c) {
	Body *b = (Body*) malloc(sizeof(Body));
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->c = c;
	b->name = NULL;
	return b;
}

Body *newPoint(int x, int y, char c) {
	Body *b = _defBody(x, y, 1, 1, c);
	b->draw = paintPoint;
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
	b->name = NULL;
	return b;
}

Body *newRectangle(int x, int y, int w, int h, char c,char mode){
	Body *b = _defBody(x, y, w, h, c);
	b->draw = paintRectangle;
	b->mode = mode;
	b->addStroke = _body_addStroke;
	return b;
}

Body *newCircle(int x, int y, int r, char c, char mode){
	Body *b = _defBody(x, y, r, r, c);
	b->draw = paintCircle;
	b->addStroke = _body_addStroke;
	b->mode = mode;
	return b;
}

Body *newLine(int x, int y, int size, char dir, char c) {
	Body *b = _defBody(x, y, 0, 0, c);
	if(dir=='h') {
		b->w = size;
		b->h = 0;
	} else {
		b->h = size;
		b->w = 0;
	}
	b->draw = paintLine;
	b->addStroke = _body_addStroke;
	return b;
}

Body *newTextBox(int x, int y, char *text, int wrap, char c) {
	Text *t = (Text*)malloc(sizeof(Text));
	Body *b = NULL;

	t->text = text;
	b = (Body*)t;
	b->x = x;
	b->y = y;
	b->w = wrap?(wrap>0?min(strlen(text), wrap):strlen(text)):min(strlen(text), screen.width-x);
	b->h = (strlen(text)+(b->w-1))/b->w;
	b->mode='l';
	b->c = c;
	b->name = NULL;
	b->draw = paintTextBox;
	b->addStroke = _body_addStroke;

	return b;
}

#endif