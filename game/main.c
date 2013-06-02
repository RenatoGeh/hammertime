#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int run() {
	char t[100];
	registerBody("tb1", newTextBox(5, 2, "hammertime", -1, '-'));
	registerBody("tb2", newTextBox(screen.width - 40, screen.height - 3, "\"O framework do ano\" - Todos", -1, '+'));
	registerBody("monocelha", newLine(3, 7, 15, 'h','~'));
	registerBody("eye1", newCircle(5, 11, 4, '+', 'l')); //'f' = modo 'fill'
	registerBody("eye2", newCircle(15, 11, 4, '+', 'l')); //'f' = modo 'fill'
	registerBody("iris1", newPoint(5, 11, 'O'));
	registerBody("iris2", newPoint(15, 11, 'O'));
	registerBody("nose1", newLine(9, 13, 3, 'v', '|'));
	registerBody("nose2", newLine(10, 16, 3, 'h', '_'));
	registerBody("nosedot", newPoint(9, 16, '\\'));
	registerBody("mouth", newRectangle(5, 18, 13, 3, '=', 'l'));
	registerBody("separator", newLine(24, 4, screen.height - 4, 'v', '|')); // 'v' = linha vertical
	registerBody("t1", newText(30, 7, "- Circulos", -1));
	registerBody("t2", newText(30, 8, "- Retangulos", -1));
	registerBody("t3", newText(30, 9, "- Retas", -1));
	registerBody("t4", newText(30, 10, "- Texto", -1));
	registerBody("t5", newText(32, 11, "etc...", -1));
	registerBody("box", newRectangle(28, 5, 30, 10, '.', 'l'));

	draw();
	printf("Digite o seu nome: ");
	gets(t);
	registerBody("greeting", newText(screen.width - 45, screen.height - 6, "Ola, ", -1));
	registerBody("greeting", newText(screen.width - 40, screen.height - 6, t, -1));
	killByName("iris2");
	registerBody("blink", newLine(13, 12, 5, 'h', '-'));
	draw();
	return 0;
}