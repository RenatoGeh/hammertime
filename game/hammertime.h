#ifndef HAMMERTIME
#define HAMMERTIME
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

void load();
void update(int);
void paint(int,int,char);
FILE *out = NULL;
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#include "env/env.h"
#include "list.h"
#include "body.h"
#include "awesometimer.h"
#define print(args...); {printf(args); puts("");}

char *terminal = NULL;

void clearterm() {
	int i, m = screen.width * screen.height;
	for(i = 0; i < m; i++) {
		*(terminal + i) = ' ';
	}
	system(CLEAR);
}

void paint(int x, int y, char c) {
	if(y < 0 || y >= screen.height || x < 0 || x >= screen.width) return;
	*(terminal + y * screen.width + x) = c; //x and y are flipped
}

void drawIntern() { 
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
		printf("%c", *(terminal + i));
	}
}

void updateIntern(int dt) {
	updateTimers(dt);
	update(dt);
}

int main(int argn, char ** args) {
	struct timeval *t1, *t2 = NULL, *temp = NULL;
	int dt, i, j;
	out = fopen("out.txt", "w");

	refreshScreen();
	screen.height--;
	terminal = (char*) malloc(sizeof(char) * screen.width * screen.height);
	clearterm();
	initBodies();

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