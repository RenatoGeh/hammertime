#include "hammertime.h"

Body *newHeader(int x, int y, char *text, int wrap) {
	Body *b = newTextBox(x, y, text, wrap, ' ');
	Stroke *s = newStroke(4, newBorder("="), newBorder("+"), newBorder("="), newBorder("+"));
	b->addStroke(b,s);
	setStrokeJoint(s, '+');
	return b;
}

int drawSide(int page) {
	int i, n=3;
	char *contents[] = {"Introduction", "Bodies", "Tables"};

	registerBody(NULL, newTextBox(10, 1, "  HAMMERTIME  ", -1, '#'));
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
	return n;
}

void drawBoard(int page) {
	switch(page) {
		case 0:
			registerBody(NULL, newHeader(60, 1, "INTRODUCTION", -1));

			registerBody(NULL, newText(65, 9, "STOP!", 0));
			registerBody(NULL, newText(40, 12, "    Welcome to Hammertime, a text-based \"visual\" framework, made with and functional with the language C.", 60));
			registerBody(NULL, newText(40, 15, "    The original idea was to create a simple yet useful framework to use in projects using C, that didn't require much knowledge in programming", 60));

			registerBody(NULL, newText(40, 19, "    This little guide will help you with the basics of Hammertime. The window on the left indicates the page you're on. To proceed to another page, type its number and press enter or type 'prev' (p), 'next' (n).", 60));
			registerBody(NULL, newText(40,27, " For more information, questions or a more detailed guide, check our wiki at:",0));

			registerBody(NULL, newText(45, 30, "https://github.com/RenatoGeh/hammertime/wiki", 0));
		break;
		case 1:
		break;
		case 2:
			registerBody(NULL, newHeader(60, 1, "Tables!", -1));

			registerBody(NULL, newText(45, 9, "Structure:", 0));
			registerBody(NULL, newText(40, 12, "    Tables are matrices. They are used to separate the screen into various 'mini-screens', with each having one Body in  each square.", 60));
			//registerBody(NULL, newText(40, 15, "    "))
		break;
	}
}

void handleInput(int *page, int n, char* input) {
	if(input[0]>='0' && input[0]<='9')
		*page=input[0]-'0';
	else if(*page<n-1 && ((input[0]=='n'&&input[1]=='\0') || !strcmp(input, "next")))
		(*page)++;
	else if(*page>0 && ((input[0]=='p'&&input[1]=='\0') || !strcmp(input, "prev")))
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
		registerBody(NULL, line);

		draw();
		gets(input);

		handleInput(&page, npage, input);
		
		clearAndRefresh();
		clearBodies();
	} while(strcmp(input, "exit"));

	return 0;
}