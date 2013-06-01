#ifndef BODY
#define BODY

#include <stdlib.h>
#include "stroke.h"

#define range(a, b, r) (a>=(b-r) && a<=(b+r))

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

#include "table.h"

void _body_addStroke(Body *b, Stroke *s) {
	int i;
	b->stroke = s;
	s->owner = &(b->c);
	for(i=0;i<s->size;i++)
		if(s->border[i]!=NULL)
			s->prev(s, i);
}

void paintRectangle(Body *self) {
	int i, j, x = self->x, y = self->y;
	int w=self->w, h=self->h;
	Stroke *s = self->stroke;
	int nil = s==NULL;
	char c = self->c;

	for(i=x;i<=x+w;i++) {
		paint(i, y, nil?c:(c=s->next(s, _STROKE_TOP)));
		paint(i, y+h, border_exists(s, _STROKE_BOTTOM)==1?s->next(s, _STROKE_BOTTOM):c);
		if(!nil && s->joint != '\0')
			if(i==x || i==x+w) {
				paint(i, y, s->joint);
				paint(i, y+h, s->joint);
			}
	}
	for(i=y+1;i<y+h;i++) {
		paint(x, i, nil?c:(c=s->next(s, _STROKE_LEFT)));
		paint(x+w, i, border_exists(s, _STROKE_RIGHT)==1?s->next(s, _STROKE_RIGHT):c);
	}

	if(self->mode=='f')
		for(i=x+1;i<x+w;i++)
			for(j=y+1;j<y+h;j++)
				paint(i, j, c);
}

void paintCircle(Body *self) {
	int i, j, x = self->x, y = self->y, r = self->w;
	int centerX = x+r, centerY = y+r;
	int endX = x+2*r, endY = y+2*r;
	int dx, dy, dt;
	Stroke *s = self->stroke;
	int nil = s==NULL;
	char mode = self->mode;
	char c = self->c;

	for(i=x;i<=endX;i++) {
		dx = centerX-i;
		for(j=y;j<=endY;j++) {
			dy = centerY - j;
			dt = dx*dx+dy*dy;
			if(range(dt, r*r, 4))
				paint(i, j, nil?c:s->next(s, _STROKE_TOP));
			else if(mode=='f' && dt<r*r)
				paint(i, j, c);
		}
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
	self->w++;
	self->h++;
	self->x--;
	self->y--;
	paintRectangle(self);
	self->w--;
	self->h--;
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
	int i, x=self->x, y=self->y;
	Stroke *s = self->stroke;
	int nil = s==NULL;

	if(self->h == 0)  //vertical
		for(i = 0; i < self->w; i++)
			paint(x + i, y, nil?self->c:s->next(s, _STROKE_TOP));
	else  //horizontal
		for(i = 0; i < self->h; i++)
			paint(x, y + i, nil?self->c:s->next(s, _STROKE_TOP));

	if(!nil && s->joint!='\0') {
		paint(x, y, s->joint);
		paint(x+self->w, y+self->h, s->joint);
	}
}

void initBodies() {
	bodies = newList();
}

Body *_defBody(int x, int y, int w, int h, char c, void (*draw)(Body*)) {
	Body *b = (Body*)malloc(sizeof(Body));
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->c = c;
	b->name = NULL;
	b->draw = draw;
	b->stroke = NULL;
	return b;
}

Body *newPoint(int x, int y, char c) {
	Body *b = _defBody(x, y, 1, 1, c, paintPoint);
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

Body *newRectangle(int x, int y, int w, int h, char c, char mode){
	Body *b = _defBody(x, y, w, h, c, paintRectangle);
	b->mode = mode;
	b->addStroke = _body_addStroke;
	return b;
}

Body *newCircle(int x, int y, int r, char c, char mode){
	Body *b = _defBody(x, y, r, r, c, paintCircle);
	b->addStroke = _body_addStroke;
	b->mode = mode;
	return b;
}

Body *newLine(int x, int y, int size, char dir, char c) {
	Body *b = _defBody(x, y, 0, 0, c, paintLine);
	if(dir=='h') {
		b->w = size;
		b->h = 0;
	} else {
		b->h = size;
		b->w = 0;
	}
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