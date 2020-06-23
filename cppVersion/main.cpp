#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include "BearLibTerminal.h"
#include "ent.h"
#include "map.h"
#define MAXW 80
#define MAXH 40
using namespace std;

 
gameMap gmap(MAXW - 4, MAXH);
Entity player(5, 5, '@');




void gameLoop()
{

 
  int key;
  srand(time(0));
  player.move(0,0);
  while ((key = terminal_read()) != TK_Q)
  {
    gmap.draw();
  	switch (key) {
  	case TK_UP: player.move(0,-1); break;
  	case TK_DOWN: player.move(0,1);  break;
  	case TK_LEFT: player.move(-1,0);  break;
  	case TK_RIGHT: player.move(1,0); break;
  	default: break;
    }
        terminal_layer(3);
        terminal_refresh();
  } 
}

int main(int argc, char *argv[])
{
 terminal_open();
 terminal_set("window: title='rr tut in c++', size=80x40");
 terminal_layer(0);
 terminal_color("blue");
 gmap.draw();
 terminal_refresh();
 terminal_layer(1);
 terminal_color("purple");
 terminal_print(15, 2, "Hey, Universe!\n");
 gameLoop();
 terminal_close();
 return 0;
}
