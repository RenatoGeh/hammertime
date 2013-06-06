#include "hammertime.h"

void basics() {
	/*************** HAMMERTIME BASICS ***************/

	/* Creating a Text Body:
	 * newText accepts four arguments:
	 *
	 *		1. The x-axis coordinate.
	 *		2. The y-axis coordinate.
	 *		3. A String with the text.
	 *		4. Wrap mode:
	 *			= -1 never wraps.
	 *			= 0 wraps on end of screen.
	 *			= n>0 wraps after n characters.
	 *
	 *	Hammertime works the same way as most frameworks,
	 *	the origin (0,0) is set to be the top-left corner 
	 * of the screen.
	 * 
	 * Note: '\n' does not work very well with Hammertime's Text. 	
	*/
	Body *caption = newText(5, 2, "Hello Hammertime!", 0);

	/* Registering a Body:
	 * registerBody accepts two arguments:
	 *		
	 *		1. A name for the Body.
	 *		2. The pointer to the Body.
	 *
	 *	Names will be used to 'kill' or 'get' Bodies.
	*/
	registerBody("hello", caption);

	/* Drawing a Rectangle:
	 * newRectangle accepts six arguments:
	 *
	 *		1. The x-axis coordinate.
	 *		2. The y-axis coordinate.
	 *		3. The rectangle's width.
	 *		4. The rectangle's height.
	 *		5. The rectangle's drawing character.
	 *		6. Draw mode:
	 *			= 'l' line mode -> draws the shape's contour.
	 *			= 'f' fill mode -> fills the shape completely.
	 *
	 *	The drawing character will be used to draw the shape.
	 * This character will be used both in line and fill mode,
	 * and will also work as a 'default paint' when we see
	 * Strokes.
	 * All Bodies are positioned at (x,y) where x and y are 
	 * the top left corner of the object.
	*/
	Body *rect = newRectangle(5, 5, 8, 4, '~', 'f');
	registerBody("rect", rect);

	/* Text + Rectangle = TextBox:
	 *	newTextBox accepts five arguments: 
	 *
	 *		1. The x-axis coordinate.
	 *		2. The y-axis coordinate.
	 *		3. A String with the desired text.
	 *		4. Wrap mode.
	 *		5. The rectangle's drawing character.
	 *	
	 *	TextBox automatically calculates the width and height
	 *	necessary for drawing the rectangle according to the
	 * given text.
	 * Text will be 'glued in' into the Rectangle, meaning there
	 * will be no spacing between the outline and the text.
	 * We will later see how we can override that with the use
	 * of Tables.
	*/
	Body *tb = newTextBox(5, 12, "Help! I'm trapped!", 9, '#');
	registerBody("tb", tb);

	/* Goin' round (Circle):
	 * newCircle accepts five arguments:
	 *
	 *		1. The x-axis coordinate.
	 *		2. The y-axis coordinate.
	 *		3. The circle's radius.
	 *		4. The drawing character.
	 *		5. Draw mode.
	 *		
	 * In Hammertime Circles are actually "pseudo-circles" due to
	 * the console's font dimensions. If the font's width is different
	 * than its height, we will get an ellipse opposed to a circle.
	 * This could be fixed by getting the console's current font, but
	 * due to portability issues and OS dependent requirements, we have
	 * left it this way for now.
	*/
	Body *circle = newCircle(30, 2, 5, 'O', 'l');
	registerBody("circle", circle);

	/* Point:
	 * newPoint accepts three arguments:
	 *
	 *		1. The x-axis coordinate.
	 *		2. The y-axis coordinate.
	 *		3. The drawing character.
	 *
	 *	Points are the most basic shapes in Hammertime. They
	 * are consisted of only one character.
	 * In this tutorial we've drawn the point in the center of
	 * the previous Body, a circle.
	*/
	Body *point = newPoint(35, 7, '*');
	registerBody("point", point);

	/* Lines:
	 * newLine accepts five arguments:
	 *
	 *		1. The x-axis coordinate.
	 *		2. The y-axis coordinate.
	 *		3. The size of the line.
	 *		4. Its direction:
	 *			- 'h'=horizontal
	 *			- 'v'=vertical
	 *		5. The drawing character.
	 *
	 *	For now, lines are only vertical or horizontal. We are
	 *	planning on creating a Function Body, in which the user
	 * inputs the mathematical function and Hammertime draws it.
	 * This will then be the most efficient (and easiest) way to
	 * create horizontal or vertical line. 
	*/
	Body *line = newLine(5, 20, 40, 'h', '_');
	registerBody("line", line);

	/* Drawing:
	 * draw accepts no arguments.
	 * 
	 * For Hammertime to know that you're done and that you
	 * want to actually draw what you've registered, you must
	 * call 'draw'.
	 * Drawing will cause all the registered Bodies to be drawn
	 * in the order that they were added, meaning that objects that
	 * intersect one another will have their intersection overriden
	 * by the last registered Body's drawing character.
	*/
	draw();
}

int run() {
	char *foo = (char*)malloc(sizeof(char));

	basics();
	gets(foo);

	clearAndRefresh();
	clearBodies();

	draw();
}