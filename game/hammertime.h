#ifndef HAMMERTIME
#define HAMMERTIME
#include <stdio.h>
#include <sys/time.h>

void load();
void update(int);
void paint(int,int,char);
FILE *out = NULL;

#include "env/env.h"
#define WIDTH 80
#define HEIGHT 23
#include "list.h"
#include "body.h"
#include "awesometimer.h"
#define print(args...); {printf(args); puts("");}

char terminal[HEIGHT][WIDTH+1];

void clearterm() {
	static int i, j;
	for(i=0; i<HEIGHT; i++) {
		for(j=0; j<WIDTH; j++)
			terminal[i][j] = ' ';
		terminal[i][WIDTH] = '\0';
	}
	system(CLEAR);
}

void paint(int x, int y, char c) {
	if(y<0 || y>=HEIGHT || x<0 || x>=WIDTH) return;
	terminal[y][x] = c; //x and y are flipped
}

void drawIntern() { 
	static int i;
	Node *n = NULL;
	Body *b = NULL;

	clearterm();
	n = (Node*) bodies->head;
	while(n) {
		b = (Body*) n->value;
		b->draw(b);
		n = n->next;
	}

	for(i=0; i<HEIGHT; i++){
		printf("%s", terminal[i]);
	}
}

void updateIntern(int dt) {
	updateTimers(dt);
	update(dt);
}

int main(int argn, char ** args) {
	struct timeval *t1, *t2 = NULL, *temp = NULL;
	int dt, i, j;
	clearterm();

	out = fopen("out.txt", "w");

	refreshScreen();

	load(argn, args);
	t1 = malloc(sizeof(struct timeval));
	t2 = malloc(sizeof(struct timeval));
	registerTimer(newAwesomeTimer(1000, drawIntern));
	drawIntern();
	gettimeofday(t1, NULL);
	while(1) {
		do {
			gettimeofday(t2, NULL);
			dt = ((t2->tv_usec/1000 + 1000 *t2->tv_sec) - (t1->tv_usec/1000 + 1000*t1->tv_sec));
		}while(dt == 0);
		updateIntern(dt);
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
}

#endif
