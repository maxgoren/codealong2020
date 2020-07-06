#include "master.h"

void drawAll(Map map)
{
int x, y, sx, sy;
char marker[20];
int offsetY = 6;
int offsetX = 1;
for (sx = offsetX; sx < offsetX + map.width; sx++)
{
   x = sx - offsetX;
   for (sy = offsetY; sy < offsetY + map.height; sy++)
   {
    y = sy - offsetY;
    if (map.layout[x][y].blocks == false)
    {
     //sprintf(marker, "%d", map.layout[x][y].isinRoom);
     terminal_layer(0);
     terminal_bkcolor("#add8e6");
     terminal_color("flame");
     terminal_print(sx, sy, " ");
   } else {
     terminal_bkcolor("black");
     terminal_color("dark grey");
     terminal_print(sx , sy, " ");
   }
   if (map.layout[x][y].border == true)
   {
    terminal_layer(1);
    terminal_color("dark grey");
    terminal_print(sx, sy, "X");
   }
   terminal_layer(2);
   for (auto m = map.badGuys.begin(); m != map.badGuys.end(); m++)
   {
    terminal_color(m->col);
     m->render();
   }
  }
 }
terminal_layer(0);
terminal_bkcolor("#cecece");
terminal_print(1,6, " ");
}

void handle_keys(int k, ent* player, Map* map, std::vector<std::string>* gamelog)
{
  switch (k) {
  	case TK_UP:
  	 player->move(*map, 0, -1); player->dir = North;
  	 break;
  	case TK_DOWN:
  	 player->move(*map, 0, 1); player->dir = South;
  	 break;
  	case TK_LEFT:
  	 player->move(*map, -1, 0); player->dir = West;
  	 break;
  	case TK_RIGHT:
  	 player->move(*map, 1, 0); player->dir = East;
  	 break;
	case TK_K:
	 player->kick(*map, gamelog);
  	default: break;
  }
}

int main() {
 int k;
 std::vector<std::string> gamelog;
 Map map(80,40);
 Gui gui(6, 1, 80, 40, 100, 45); 
 terminal_open();
 terminal_set("window: size=100x45");
  gui.drawGui(&gamelog);
  map.genRect(11, 12);
  ent player(map.spx, map.spy,"aT", '@', color_from_name("magenta"));
  map.spawnMonsters(13);
  drawAll(map);
  player.render();
   terminal_refresh();
 while((k = terminal_read()) != TK_Q)
  {
   handle_keys(k, &player, &map, &gamelog);
   terminal_clear();
   player.render();
   drawAll(map);
   gui.drawGui(&gamelog);
  drawAll(map);
   terminal_refresh();
  }
  terminal_close;
  return 0;
}
