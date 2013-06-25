#include "hammertime.h"

Body *newHeader(int x, int y, char *text, int wrap) {
	Body *b = newTextBox(x, y, text, wrap, ' ');
	Stroke *s = newStroke(4, newBorder("="), newBorder("+"), newBorder("="), newBorder("+"));
	b->addStroke(b,s);
	setStrokeJoint(s, '+');
	return b;
}

int drawSide(int page) {
	int i, j, n=3;
	char *contents[] = {"Introduction", "Hello Hammertime!", "The Basics"};
	char str[100][100];

	registerBody("NULL", newTextBox(10, 1, "  HAMMERTIME  ", -1, '#'));
	registerBody("NULL", newLine(2, 4, 150, 'h', '-'));
	registerBody("NULL", newText(10, 5, "Table of Content", 0));
	registerBody("NULL", newLine(10, 6, 16, 'h', '_'));
	
	for(i=0;i<n;i++) {
		sprintf(str[2*i], "t%d", i);
		sprintf(str[2*i+1], "%d.    %s", i, contents[i]);
		registerBody(str[2*i], newText(8, 10+2*i, str[2*i+1], 0));
	}
	
	registerBody("NULL", newPoint(13, 10+2*page, '*'));
	return n;
}

void drawBoard(int page) {
	switch(page) {
		case 0:
			registerBody("NULL", newHeader(60, 1, "INTRODUCTION", -1));

			registerBody("NULL", newText(65, 9, "STOP!", 0));
			registerBody("NULL", newText(40, 12, "    Welcome to *hammertime*, a text-based \"visual\" framework made and functional with the language C.", max(60, screen.width-40)));
			registerBody("NULL", newText(40, 15, "    The original idea was to create a simple yet useful     framework to use in projects using C, that didn't require   much knowledge in programming.", max(60, screen.width-40)));

			registerBody("NULL", newText(40, 19, "    This little guide will help you with the basics of      *hammertime*. The window on the left indicates the page     you're on. To proceed to the next page, type 'next' (or     'n'). To return to the previous page, type 'prev' (or 'p'). Or if you want you can just type the page's number and pressenter.", max(60, screen.width-40)));
			registerBody("NULL", newText(40, 26, "    Type 'exit' at any time to leave this guide.", 0));

			registerBody("NULL", newText(45, 32, "https://github.com/RenatoGeh/hammertime/wiki", 0));
		break;
		case 1:
			registerBody("NULL", newHeader(60, 1, "USING *HAMMERTIME*", -1));

			registerBody("NULL", newText(40, 10, "    First of all, lets see how to include *hammertime* in   any C source file.", 60));
			registerBody("NULL", newText(40, 13, "    Make sure all files from *hammertime* are in the same   folder as your project.", 60));
			registerBody("NULL", newText(40, 16, "    Just as any other library, you'll need to include       \"hammertime.h\" in the beginning of your C project(#include  \"hammertime.h\").", 60));
			registerBody("NULL", newText(40, 20, "    Instead of a \"int main()\" function, you'll write the    things *hammertime* will print in a \"int run()\" function.", 60));
			registerBody("NULL", newText(40, 23, "    But just as a normal C source file, you can write other functions as well.", 60));
			registerBody("NULL", newText(40, 25, "    Example of a simple *hammertime* project:", 60));
			registerBody("NULL", newTextBox(40, 29, "#include \"hammertime.h\"", 40, '#'));
		break;
		case 2:
			registerBody("NULL", newHeader(60, 1, "BODIES AND BASIC DRAWING", -1));

			registerBody("NULL", newText(40, 10, "    In *hammertime*, the basic thing you'll need to learn is how to create (or register) \"bodies\" and make them visible.", 60));
			registerBody("NULL", newText(40, 13, "    A body is some sort of object, and it may vary from a simple text to a circle made of \"$\".", 60));
			registerBody("NULL", newText(40, 16, "    To create a simple body you follow this model:", 60));
			registerBody("NULL", newText(40, 19, "       registerBody(name, newThing(thing parameters));", 60));
		break;
	}
}

char isKeyword(char *input, char *key) {
	return (input[0]==key[0] && input[1]=='\0') || !strcmp(input, key);
}

void handleInput(int *page, int n, char* input) {
	if(input[0]>='0' && input[0]<='9' && input[0]-'0'<n)
		*page=input[0]-'0';
	else if(*page<n-1 && isKeyword(input, "next"))
		(*page)++;
	else if(*page>0 && isKeyword(input, "prev"))
		(*page)--;
}

int run() {
	int page = 0, npage;
	char *input = (char*)malloc(sizeof(char));
	do {
		npage = drawSide(page);
		drawBoard(page);

		Body *line = newLine(35, 1, 60, 'v', '-');
		Stroke *lineStroke = newStroke(1, newBorder("|"));
		line->addStroke(line, lineStroke);
		setStrokeJoint(lineStroke, '#');
		registerBody("NULL", line);

		draw();
		gets(input);

		handleInput(&page, npage, input);
		
		clearAndRefresh();
		clearBodies();
	} while(!isKeyword(input, "exit"));

	return 0;
}