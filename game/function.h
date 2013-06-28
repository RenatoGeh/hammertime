#ifndef FUNCTION
#define FUNCTION

#define _MAX_TERMS 15
#define _FUNCTION_RANGE 4

struct function_utils {
	void (*addAxis)(void);
} function;

typedef struct funcstruct {
	Body base;
	double (*f)(double);
	char *(*toString)(char *, struct funcstruct *);
} Function;

/* This is gonna be tricky. Do I have to test every instance of x? And if so,
 * how do I merge all that into a function formula? Wouldn't I have to test
 * every instance of x, meaning till infinity? I am at a lost here.
 * TODO: THE IMPOSSIBLE.
*/
char *_function_toString(char *str, Function *f) {
	return NULL;
}

void paintFunction(Body* b) {
	Function *func = (Function*)b;
	double i, f;
	char c = b->c;

	for(i=-screen.width/2;i<=screen.width;i+=0.01) {
		f = func->f(i);
		paint(10*(i+screen.width/2), _poly_round((screen.height-50*f)-screen.height/2), c);
		//printf("x=%f\tsin(x)=%f\n", i, func->f(i));
	}
}

Body *newFunction(int x, int y, int w, int h, char c, double (*f)(double x)) {
	Function *func = (Function*)malloc(sizeof(Function));
	Body *base;

	func->f = f;
	func->toString = _function_toString;

	base = (Body*)func;
	base->x = x; base->y = y;
	base->w = w; base->h = h;
	base->c = c;
	base->name = NULL;
	base->draw = paintFunction;
	base->stroke = NULL;

	return base;
}

typedef struct polystruct {
	Body base;
	int degree;
	int terms[_MAX_TERMS];

	char *(*toString)(char *, struct polystruct *);
} Polynomial;

void _function_addAxis() {
	registerBody("_function_xaxis", newLine(0, screen.height/2, screen.width, 'h', '-'));
	registerBody("_function_yaxis", newLine(screen.width/2, 0, screen.height, 'v', '|'));

	registerBody("_function_xaxis_label", newText(0, screen.height/2-1, "x-axis", 0));
	registerBody("_function_yaxis_label", newText(screen.width/2+1, 0, "y-axis", 1));
}

void _function_init() {
	function.addAxis = _function_addAxis;
}

void _poly_conpts(int x0, int y0, int x1, int y1, Polynomial *poly) {
	int dx=x1-x0, dy=y1-y0;
	int i, j;
}

int _poly_round(double n) {
	int k = (int)n;
	if(n-k<0.5) return (int)n;
	else return (int)n+1;
}

void paintPolynomial(Body *b) {
	Polynomial *poly = (Polynomial*)b;
	int degree=poly->degree;
	int x=b->x, y=b->y, w=b->w, h=b->h;
	double i;
	int f, p, j, l;
	Stroke *s = b->stroke;
	char nil = s==NULL;
	char c = b->c;

	for(i=x;i<=x+w;i+=0.05) {
		for(f=0,j=0;j<=degree;j++) {
			for(l=0,p=1;l<degree-j;l++,p*=i);
			//printf("%d\t%d\n", p, poly->terms[j]);
			f+=poly->terms[j]*p;
		}
		paint(i+screen.width/2, _poly_round((screen.height-f)-screen.height/2), nil?c:s->next(s, _STROKE_TOP));
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
		if((term=term<0?-term:term)>1 && i<degree) {
			for(l=0;term>0;term/=10,l++,j++) {
				str[j]='0'+term%10;
				if(l>0) {
					k=str[j];
					str[j]=str[j-1];
					str[j-1]=k;
				}
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
	for(i=0;i<degree+1;i++)
		poly->terms[i] = va_arg(terms, int);
	va_end(terms);

	b = (Body*)poly;
	b->x = x; b->y = y;
	b->w = w; b->h = h;
	b->c = c;
	b->name = NULL;
	b->draw = paintPolynomial;
	b->stroke = NULL;

	if(b->w<0) b->w=screen.width;
	if(b->h<0) b->h=screen.height;
	if(b->x<=0) b->x=-screen.width/2; 
	if(b->y<=0) b->y=0;

	return b;
}

#endif