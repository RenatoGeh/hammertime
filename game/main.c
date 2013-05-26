#include "hammertime.h"
#include <stdio.h>
#include <stdlib.h>

void load() {
	registerBody(newPoint(20,10));
	registerBody(newText(10,12,"hey, dude. I'm wrapping text!", 15));
	registerBody(newText(WIDTH - 13, 4, "Automatic wrapping like a boss.", 0));
	registerBody(newText(WIDTH - 13, 10, "But that's optional.", -1));
}

void update(int dt) {

}