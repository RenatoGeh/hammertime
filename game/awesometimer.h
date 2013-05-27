#ifndef AWESOMETIMER
#define AWESOMETIMER
#include <stdlib.h>

struct AwesomeTimerStruct {
	void (*func)(void);
	long timeToSet;
	long currentTime;
	void (*updateSelf)(struct AwesomeTimerStruct*, int);
};

typedef struct AwesomeTimerStruct AwesomeTimer;
AwesomeTimer* timers[1000];
int tsize = 0;

void updateSelfTimer(AwesomeTimer *self, int dt) {
	self->currentTime += dt;
	if(self->currentTime >= self->timeToSet) {
		self->currentTime -= self->timeToSet;
		(*self->func)();
	}
}

void registerTimer(AwesomeTimer *at) {
	timers[tsize++] = at;
}

AwesomeTimer *newAwesomeTimer(int timeToCall, void (*funcToCall)(void)) {
	AwesomeTimer *at = (AwesomeTimer*) malloc(sizeof(AwesomeTimer));
	at->currentTime = 0;
	at->func = funcToCall;
	at->timeToSet = timeToCall;
	at->updateSelf = updateSelfTimer;
	return at;
}

void updateTimers(int dt) {
	static unsigned i;
	for(i = 0; i < tsize; i++)
		timers[i]->updateSelf(timers[i], dt);
}
#endif
