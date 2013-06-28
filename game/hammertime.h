#ifndef HAMMERTIME
#define HAMMERTIME
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

int run();
void paint(int,int,char);
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#include "env/env.h"
#include "list.h"
#include "body.h"
#define print(args...); {printf(args); puts("");}

char *terminal = NULL;

void clearterm() {
	int i, m = screen.width * screen.height;
	fflush(stdout);
	system(CLEAR);
	for(i = 0; i < m; i++) {
		terminal[i] = ' ';
	}
}

void clearAndRefresh() {
	refreshScreen();
	free(terminal);
	terminal = (char*) malloc(sizeof(char) * screen.width * screen.height);
	clearterm();
}

void paint(int x, int y, char c) {
	if(y < 0 || y >= screen.height || x < 0 || x >= screen.width) return;
	terminal[y * screen.width + x] = c; //x and y are flipped
}

void draw() { 
	int i, m = screen.width * screen.height;
	Node *n = NULL;
	Body *b = NULL;

	clearterm();
	n = (Node*) bodies->head;
	while(n) {
		b = (Body*) n->value;
		b->draw(b);
		n = n->next;
	}

	for(i = 0; i < m; i++){
		printf("%c", terminal[i]);
	}
	fflush(stdout);
}

void closeAll() {
	free(terminal);
	clearBodies();
	free(bodies);
}

int main(int argn, char ** args) {
	int ret;

	_function_init();
	_stroke_init();

	clearAndRefresh();
	
	initBodies();

	ret = run(argn, args);

	closeAll();

	return ret;
}

#endif