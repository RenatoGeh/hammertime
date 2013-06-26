#ifndef FUNCTION
#define FUNCTION

#define _MAX_TERMS 15
#define _FUNCTION_RANGE 4

typedef struct polystruct {
	Body base;
	int degree;
	int terms[_MAX_TERMS];

	char *(*toString)(char *, struct polystruct *);
} Polynomial;

void _poly_conpts(int x0, int y0, int x1, int y1, Polynomial *poly) {
	int dx=x1-x0, dy=y1-y0;
	int i, j;
}

void paintPolynomial(Body *b) {
	Polynomial *poly = (Polynomial*)b;
	int degree=poly->degree;
	int x=b->x, y=b->y, w=b->w, h=b->h;
	int f, p, i, j, l;
	Stroke *s = b->stroke;
	char nil = s==NULL;
	char c = b->c;

	if(w<0) w=screen.width;
	if(h<0) h=screen.height;
	if(x<=0) x=-screen.width/2; if(y<=0) y=0;

	for(i=x;i<=x+w;i++) {
		for(f=0,j=0;j<=degree;j++) {
			for(l=0,p=1;l<degree-j;l++,p*=i);
			//printf("%d\t%d\n", p, poly->terms[j]);
			f+=poly->terms[j]*p;
		}
		paint(i+screen.width/2, (screen.height-f)-screen.height/2, nil?c:s->next(s, _STROKE_TOP));
	}
}

char *_poly_toString(char *str, Polynomial *poly) {
	int i, degree=poly->degree+1, term;
	int j=0, l, k;
	
	str[j++]='f'; str[j++]='('; str[j++]='x'; str[j++]=')'; str[j++]='=';
	for(i=0;i<degree;i++) {
		term = poly->terms[i];
		if(term==0) continue;
		if(i!=0) {
			if(term>=0) str[j++]='+';
			else str[j++]='-';
		}
		if((term=term<0?-term:term)>1 && i<degree)
			for(l=0;term>0;term/=10,l++,j++) {
				str[j]='0'+term%10;
				if(l>0) {
					k=str[j];
					str[j]=str[j-1];
					str[j-1]=k;
				}
			}
		if(i<degree-1) {
			str[j++]='x'; 
			if((term=poly->degree-i)>1) {
				str[j++]='^';
				for(l=0;term>0;term/=10,l++,j++) {
					str[j]='0'+term%10;
					if(l>0) {
						k=str[j];
						str[j]=str[j-1];
						str[j-1]=k;
					}
				}
			}
		}
	}
	str[j] = '\0';

	return str;
}

Body *newPolynomial(int x, int y, int w, int h, char c, int degree, ...) {
	Body *b;
	Polynomial *poly = (Polynomial*)malloc(sizeof(Polynomial));
	va_list terms;
	int i;

	poly->degree = degree;
	poly->toString = _poly_toString;

	va_start(terms, degree);
	for(i=0;i<degree+1;i++) {
		poly->terms[i] = va_arg(terms, int);
		printf(">%d\n", poly->terms[i]);
	}
	va_end(terms);

	b = (Body*)poly;
	b->x = x; b->y = y;
	b->w = w; b->h = h;
	b->c = c;
	b->name = NULL;
	b->draw = paintPolynomial;
	b->stroke = NULL;

	return b;
}

#endif