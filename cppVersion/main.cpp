#include "BearLibTerminal.h"
#include "map.h"
#include <iostream>
void drawAll(Map dungeon)
{
	int x, y;
terminal_layer(1);
for (y = 5; y < 40; y++) {
	for (x = 0; x < 70; x++) {
			if (dungeon.layout[x][y].blocking == false)
			{
				terminal_color("darker red");
				terminal_print(x , y, ".");
				
			}
			if (dungeon.layout[x][y].borders == true) {
				terminal_color("dark grey");
				terminal_print(x, y, "#");
			}

			}
		}
}

void gameLoop() {
	Map dungeon(40, 70);
	drawAll(dungeon);
	int key,playerx = 7,playery = 7;
	while ((key = terminal_read()) != TK_Q) {
		switch (key) {
		case TK_UP:
			playery--;
			break;
		case TK_DOWN:
			playery++;
			break;
		case TK_RIGHT:
			playerx++;
			break;
		case TK_LEFT:
			playerx--;
			break;
		default:
			break;
		}
		terminal_clear();
		drawAll(dungeon);
		terminal_layer(2);
		terminal_print(playerx, playery, "@");
		terminal_refresh();
	}
}


int main(int argc, char *argv[])
{
	
	srand(time(NULL));
	terminal_open();
	terminal_set("window: title='BearLib C++ tutorial', size=80x40");
	terminal_layer(1);
	terminal_print(20, 20, "Hello, World!");
	terminal_print(7, 7, "@");
	terminal_refresh();
	gameLoop();
	terminal_close();
	return 0;
}
