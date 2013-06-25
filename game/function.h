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
	if(x<0) x=0; if(y<0) y=0;

	/*for(i=x;i<=x+w;i++) {
		for(j=0,f=0;j<degree+1;j++) {
			f+=(r=poly->terms[j]);
			for(l=0,p=1;l<degree;l++,p*=r);
			f*=p;
		}
		paint(i, f, nil?c:s->next(s, _STROKE_TOP));
	}*/

	for(i=x;i<=x+w;i++) {
		for(f=0,j=0;j<=degree;j++) {
			for(l=0,p=1;l<degree-j;l++,p*=i);
			//printf("%d\t%d\n", p, poly->terms[j]);
			f+=poly->terms[j]*p;
		}
		paint(i, screen.height-f, nil?c:s->next(s, _STROKE_TOP));
	}

	/*for(i=x;i<=x+w;i++,degree--) {
		f = poly->terms[l];
		for(j=0,p=1;j<degree;j++,p*=i);
		printf("x=%d\ty=%d\tf=%d\tp=%d\n", i, f*p, f, p);
		//for(r=-_FUNCTION_RANGE;r<=_FUNCTION_RANGE;i++)
			paint(r+i, r+f*p, nil?c:s->next(s, _STROKE_TOP));
	}*/
}

char *_poly_toString(char *str, Polynomial *poly) {
	int i, degree=poly->degree+1, term;
	int j=0;
	
	str[j++]='f'; str[j++]='('; str[j++]='x'; str[j++]=')'; str[j++]='=';
	for(i=0;i<degree;i++) {
		term = poly->terms[i];
		if(term==0) continue;
		if(i!=0) {
			if(term>=0) str[j++]='+';
			else str[j++]='-';
		}
		if((term=term<0?-term:term)>1)
			for(;term>0;term/=10)
				str[j++]='0'+term%10;
		if(i<degree-1) {
			str[j++]='x'; 
			if((term=poly->degree-i)>1) {
				str[j++]='^';
				for(;term>0;term/=10)
					str[j++]='0'+term%10;
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