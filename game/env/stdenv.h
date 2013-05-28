#ifndef STDENV
#define STDENV

#include <sys/ioctl.h>
#include <unistd.h>

static struct winsize envscreen;

void refreshScreen() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &envscreen);
	screen.width = envscreen.ws_col;
	screen.height = envscreen.ws_row - 1;
}

int getConsoleWidth() {return screen.width;}
int getConsoleHeight() {return screen.height;}

int getConsoleX() {return screen.x;}
int getConsoleY() {return screen.y;}

#endif
