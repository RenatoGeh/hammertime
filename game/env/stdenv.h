#ifndef STDENV
#define STDENV

#include <sys/ioctl.h>
#include <unistd.h>

static struct winsize envscreen;

void refreshScreen() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &envscreen);
	screen.width = envscreen.ws_row;
	screen.height = envscreen.ws_col;
}

int getConsoleWidth() {return screen.width;}
int getConsoleHeight() {return screen.height;}

int getConsoleX() {return screen.x;}
int getConsoleY() {return screen.y;}

#endif
