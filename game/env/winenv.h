#ifndef WINENV
#define WINENV

#include <windows.h>

typedef struct cscreen ConsoleScreen;
struct cscreen {
	int x;
	int y;
	int width;
	int height;
};

static ConsoleScreen SCREEN;
static CONSOLE_SCREEN_BUFFER_INFO winscreen;

void refreshScreen() {
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &winscreen);
	SCREEN.width = winscreen.srWindow.Right - winscreen.srWindow.Left + 1;
	SCREEN.height = winscreen.srWindow.Bottom - winscreen.srWindow.Top + 1;
}

void setConsoleSize(int width, int height) {
	COORD c = {width, height};
	SCREEN.width = width;
	SCREEN.height = height;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int getConsoleWidth() {return SCREEN.width;}
int getConsoleHeight() {return SCREEN.height;}

int getConsoleX() {return SCREEN.x;}
int getConsoleY() {return SCREEN.y;}

#endif
