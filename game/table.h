#ifndef TABLE
#define TABLE

#define _MAX_TABLE_LINES 50
#define _MAX_TABLE_COLS 50

typedef struct tablestruct Table;
struct tablestruct {
	Body base;
	Body *elements[_MAX_TABLE_LINES][_MAX_TABLE_COLS];
	int size;
	char c1, c2;

	int lines, cols;
	int wline, hcol;

	void (*add)(Table*, Body*, int, int, char);
	Body* (*remove)(Table*, int, int);

	Body* (*get)(Table*, int, int);
	void (*swap)(Table*, int, int, int, int);
};

void paintTable(Body *b) {
	Table *t = (Table*)b;
	int x=b->x, y=b->y, w=b->w, h=b->h;
	int lines=t->lines, cols=t->cols;
	int wline=t->wline, hcol=t->hcol;
	int i, j, size=t->size;
	Stroke *s = b->stroke;
	char nil = s==NULL;
	char c1=t->c1, c2=t->c2;

	for(i=1;i<lines;i++)
		for(j=y;j<y+h;j++)
			paint(x+i*wline, j, c1);

	for(i=1;i<cols;i++)
		for(j=x;j<x+w;j++)
			paint(j, y+i*hcol, c2);
	
	for(i=y;i<y+h;i++) paint(x, i, nil?c1:s->next(s, _STROKE_LEFT));
	for(i=x;i<x+w;i++) paint(i, y, nil?c2:s->next(s, _STROKE_TOP));
	for(i=x;i<=x+w;i++) paint(i, y+cols*hcol, nil?c2:s->next(s, _STROKE_BOTTOM));
	for(i=y;i<y+h;i++) paint(x+lines*wline, i, nil?c1:s->next(s, _STROKE_RIGHT));

	if(!nil && s->joint!='\0')
		for(i=0;i<=lines;i++)
			for(j=0;j<=cols;j++)
				paint(x+i*wline, y+j*hcol, s->joint);

	for(i=0;i<lines;i++) 
		for(j=0;j<cols;j++)
			if(t->elements[i][j]!=NULL)
				t->elements[i][j]->draw(t->elements[i][j]);
	//for(i=0;i<size;i++) t->elements[i]->draw(t->elements[i]);
}

Body *_table_get(Table *t, int x, int y) {
	return t->elements[x][y];
}

void _table_add(Table *t, Body *b, int x, int y, char centers) {
	Body base = t->base;

	if(centers) {
		b->x = (base.x+(x*t->wline)+1) + (t->wline-b->w)/2-1;
		b->y = (base.y+(y*t->hcol)+1) + (t->hcol-b->h)/2-1;
	} else {
		b->x += base.x+(x*t->wline)+1;
		b->y += base.y+(y*t->hcol)+1;
	}


	t->elements[x][y] = b;
	t->size++;
}

Body *_table_remove(Table *t, int x, int y) {
	Body base = t->base;
	Body *b = t->elements[x][y];

	b->x -= base.x+(x*t->wline)+x;
	b->y -= base.y+(y*t->hcol)+y;

	t->elements[x][y] = NULL;
	t->size--;

	return b;
}

void _table_swap(Table *t, int x1, int y1, int x2, int y2) {
	Body *b = t->remove(t, x2, y2);
	t->add(t, t->remove(t, x1, y1), x2, y2, 0);
	t->add(t, b, x1, y1, 0);
}

Body *newTable(int x, int y, int lines, int cols, int wline, int hcol, char c1, char c2) {
	Body *b = NULL;
	Table *t = (Table*)malloc(sizeof(Table));
	int i, j;

	wline = wline<0?((screen.width-1)/lines):wline;
	hcol = hcol<0?((screen.height-1)/cols):hcol;

	t->lines = lines;
	t->cols = cols;
	t->wline = wline;
	t->hcol = hcol;
	t->size = 0;

	t->add = _table_add;
	t->remove = _table_remove;
	t->get = _table_get;
	t->swap = _table_swap;
	t->c1 = c1;
	t->c2 = c2;

	for(i=0;i<lines;i++)
		for(j=0;j<cols;j++)
			t->elements[i][j]=NULL;

	b = (Body*)t;
	b->name = NULL;
	b->x = x;
	b->y = y;
	b->draw = paintTable;
	b->w = wline*lines;
	b->h = hcol*cols;
	b->stroke = NULL;
	b->c = c1;
	b->addStroke = _body_addStroke;
}

#endif