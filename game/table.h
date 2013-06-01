#ifndef TABLE
#define TABLE

#define _MAX_TABLE_LINES 50
#define _MAX_TABLE_COLS 50

typedef struct {
	Body base;
	int lines, cols;
	int wline, hcol;
	Body *elements[_MAX_TABLE_LINES][_MAX_TABLE_COLS];
} Table;

void paintTable(Body *b) {
	Table *t = (Table*)b;
}

Body *newTable(int x, int y, int lines, int cols, int wline, int hcol, char c) {
	Body *b = NULL;
	Table *t = (Table*)malloc(sizeof(Table));

	t->lines = lines;
	t->cols = cols;
	t->wline = wline;
	t->hcol = hcol;
	
	b = (Body*)t;
	b->name = NULL;
	b->x = x;
	b->y = y;
	b->draw = paintTable;
	b->w = wline*lines;
	b->h = hcol*cols;
}

#endif