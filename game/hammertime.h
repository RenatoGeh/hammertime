#ifndef HAMMERTIME
#define HAMMERTIME
#define WIDTH 80
#define HEIGHT 23
#include <stdio.h>
#include <sys/time.h>
#include "body.h"
#include "awesometimer.h"

void load();
void update(int);

char terminal[HEIGHT][WIDTH+1];

void clearterm() {
	static int i, j;
	for(i=0; i<HEIGHT; i++) {
		for(j=0; j<WIDTH; j++)
			terminal[i][j] = ' ';
		terminal[i][WIDTH] = '\0';
	}
}

void drawIntern() { 
	static int i;
	printf("\n");
	system("clear");
	for(i=0; i<HEIGHT; i++){
		printf("%s\n", terminal[i]);
	}
}

void updateIntern(int dt) {
	static int i;
	updateTimers(dt);
	clearterm();
	update(dt);
	for(i=0; i<bsize; i++)
		bodies[i]->draw(bodies[i], terminal);
}

int main(int argn, char ** args) {
	struct timeval *t1, *t2 = NULL, *temp = NULL;
	int dt, i, j;
	clearterm();

	load(argn, args);
	t1 = malloc(sizeof(struct timeval));
	t2 = malloc(sizeof(struct timeval));
	registerTimer(newAwesomeTimer(1000, drawIntern));
	gettimeofday(t1, NULL);
	while(1) {
		do {
			gettimeofday(t2, NULL);
			dt = ((t2->tv_usec/1000 + 1000 *t2->tv_sec) - (t1->tv_usec/1000 + 1000*t1->tv_sec));
		}while(dt == 0);
		update(dt);
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
}

#endif