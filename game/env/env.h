#ifndef ENV
#define ENV

typedef struct cscreen ConsoleScreen;
struct cscreen {
	int x;
	int y;
	int width;
	int height;
};

static ConsoleScreen screen;
void refreshScreen(void);

#ifdef _WIN32
	#define CLEAR "cls"
	#include "winenv.h"
#else
	#define CLEAR "clear"
	#include "stdenv.h"
#endif

#endif