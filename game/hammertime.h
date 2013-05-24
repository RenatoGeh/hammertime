#ifndef HAMMERTIME
#define HAMMERTIME
#include <stdio.h>
#include <sys/time.h>
#include "body.h"
#include "awesometimer.h"

void load();
void update(int);

void test() { 
	static int i = 0;
	printf("%d\n", ++i);
}

int main(int argn, char ** args) {
	struct timeval *t1, *t2 = NULL, *temp = NULL;
	int dt;
	AwesomeTimer *at;
	load(argn, args);
	t1 = malloc(sizeof(struct timeval));
	t2 = malloc(sizeof(struct timeval));
	at = newAwesomeTimer(33, test);
	registerTimer(at);
	gettimeofday(t1, NULL);
	while(1) {
		do {
			gettimeofday(t2, NULL);
			dt = ((t2->tv_usec/1000 + 1000 *t2->tv_sec) - (t1->tv_usec/1000 + 1000*t1->tv_sec));
		}while(dt == 0);
		update(dt);
		updateTimers(dt);
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
}

#endif