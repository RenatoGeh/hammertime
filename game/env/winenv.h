#ifndef WINENV
#define WINENV

#include <windows.h>

static CONSOLE_SCREEN_BUFFER_INFO winscreen;

void refreshScreen() {
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &winscreen);
	screen.width = winscreen.srWindow.Right - winscreen.srWindow.Left + 1;
	screen.height = winscreen.srWindow.Bottom - winscreen.srWindow.Top;
}

void setConsoleSize(int width, int height) {
	COORD c = {width, height};
	screen.width = width;
	screen.height = height;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int getConsoleWidth() {return screen.width;}
int getConsoleHeight() {return screen.height;}

int getConsoleX() {return screen.x;}
int getConsoleY() {return screen.y;}

#endif
