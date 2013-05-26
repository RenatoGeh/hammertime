#ifndef STDENV
#define STDENV

#include <sys/ioctl.h>
#include <unistd.h>

typedef struct cscreen ConsoleScreen;
struct cscreen {
	int x;
	int y;
	int width;
	int height;
};

static ConsoleScreen SCREEN;
static struct winsize envscreen;

void refreshScreen() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &envscreen);
	SCREEN.width = envscreen.ws_row;
	SCREEN.height = envscreen.ws_col;
}

int getConsoleWidth() {return SCREEN.width;}
int getConsoleHeight() {return SCREEN.height;}

int getConsoleX() {return SCREEN.x;}
int getConsoleY() {return SCREEN.y;}

#endif
