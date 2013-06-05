#include "hammertime.h"

Body *newHeader(int x, int y, char *text, int wrap, char c) {
	Body *b = newTextBox(x, y, text, wrap, c);
	Stroke *s = newStroke(4, newBorder("="), newBorder("+"), newBorder("="), newBorder("+"));
	b->addStroke(b,s);
	setStrokeJoint(s, '+');
	return b;
}

void drawSide(int page) {
	int i, n=3;
	char *contents[] = {"Introduction", "Bla", "Bla2"};

	registerBody(NULL, newTextBox(10, 1, " *HAMMERTIME* ", -1, '#'));
	registerBody(NULL, newLine(2, 4, 150, 'h', '-'));
	registerBody(NULL, newText(10, 5, "Table of Content", 0));
	registerBody(NULL, newLine(10, 6, 16, 'h', '_'));

	for(i=0;i<n;i++) {
		char *name = (char*)malloc(sizeof(char));
		char *section = (char*)malloc(sizeof(char));

		sprintf(name, "t%d", i);
		sprintf(section, "%d.    %s", i, contents[i]);
		registerBody(name, newText(8, 10+2*i, section, 0));
	}

	registerBody("", newPoint(13, 10+2*page, '*'));
}

void drawBoard(int page) {
	switch(page) {
		case 0:
			registerBody(NULL, newText(65, 9, "STOP!", 0));
			registerBody(NULL, newText(40, 12, "    Welcome to Hammertime, a text-based \"visual\" framework, made with and functional with the language C.", 60));
			registerBody(NULL, newText(40, 15, "    The original idea was to create a simple yet useful     framework to use in projects using C, that didn't require   much knowledge in programming", 60));

			registerBody(NULL, newHeader(60, 1, "INTRODUCTION", -1, '!'));
		break;
	}
}

void handleInput(int *page, char* input) {
	if(input[0]>='0' && input[0]<='9')
		*page=input[0]-'0';
	else if(!strcmp(input, "next"))
		(*page)++;
	else if(!strcmp(input, "prev"))
		(*page)--;
}

int run() {
	int page = 0;
	char *input = (char*)malloc(sizeof(char));

	do {
		drawSide(page);
		drawBoard(page);

		Body *line = newLine(35, 1, 60, 'v', '-');
		Stroke *lineStroke = newStroke(1, newBorder("|"));
		line->addStroke(line, lineStroke);
		setStrokeJoint(lineStroke, '#');
		registerBody(NULL, line);

		draw();
		gets(input);

		handleInput(&page, input);
		
		clearAndRefresh();
		clearBodies();
	} while(strcmp(input, "exit"));

	return 0;
}