  
/****************************************************************
*  MIT License
* 
*  Copyright (c) 2020 Max Goren
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
***************************************************/
#include "master.h"
bool showingmap = false;
void drawAll(Map* map, ent* player, int i)
{
int x, y, sx, sy;
char marker[20];
int offsetY = 10; 
int offsetX = 0;
double zelda;
for (sx = offsetX; sx < offsetX + map->width; sx++)
{
   x = sx - offsetX;
   for (sy = offsetY; sy < offsetY + map->height; sy++)
   {
    y = sy - offsetY;
  if (map->fov == false) {
    if (map->layout[x][y].blocks == false)
    {
     
     terminal_layer(0);
     terminal_bkcolor("#bebebe");
    terminal_color("#8b4513");
     terminal_put(sx, sy, 57643);
   } else {
     terminal_bkcolor("black");
     terminal_color("dark grey");
     terminal_print(sx , sy, " ");
   }
   if (map->layout[x][y].border == true)
   {
    terminal_layer(1);
    terminal_color("#c2c2c2");
    terminal_put(sx,sy,57643);
   }
   if (showingmap == true) {
   terminal_layer(4);
   terminal_color("++[darker] grey");
   terminal_print(sx,sy,std::to_string(map->layout[x][y].value).c_str());
   }
  } else {
  zelda = map->isInFov(x, y, player->pos.x, player->pos.y);
   //std::cout<<zelda<<"\n";
   if (zelda <= 3) {
     if (map->layout[x][y].blocks == false) {
      terminal_layer(0);
      terminal_bkcolor("#E0D937");
      terminal_color("white");
      terminal_print(sx,sy, " ");
     }
      if (map->layout[x][y].border == true) {
        terminal_layer(0);
        terminal_bkcolor("darker grey");
        terminal_print(sx, sy, " ");
      }
   } else {
     terminal_color("black");
   }
 } 
}
}  
  terminal_layer(2);
  if (map->fov == true) 
  {
    for (auto m : map->badGuys)
    {
      zelda = map->isInFov(m->pos.x, m->pos.y, player->pos.x, player->pos.y);
      if (zelda <= 3) {
        terminal_color(m->col);
        m->render();
    }
    for (auto z : map->itemList)
    {
      zelda = map->isInFov(z->pos.x, z->pos.y, player->pos.x, player->pos.y);
      if (zelda <= 3) {
         z->render();
      }
    }
    }
  } else {
    for (auto m : map->badGuys)
    {
      terminal_color(m->col);
      m->render();
    }
    for (auto z : map->itemList)
    {
      z->render();
    }
  }
  terminal_layer(0);
  terminal_bkcolor("#cecece");
  terminal_print(1,6, " ");
}


void handle_keys(int k, ent* player, Map* map, Gui* gui)
{
  Items* smoke;
  std::string msg;
  float fightDmg;
  switch (k) {
  	case TK_UP:
  	 player->move(map, 0, -1); player->dir = North;
  	 break;
  	case TK_DOWN:
  	 player->move(map, 0, 1); player->dir = South;
  	 break;
  	case TK_LEFT:
  	 player->move(map, -1, 0); player->dir = West;
  	 break;
  	case TK_RIGHT:
  	 player->move(map, 1, 0); player->dir = East;
  	 break;
    case TK_C:
     std::cout<<map->badGuys.size()<<std::endl;
     break;
     case TK_I:
     player->handleItem(map, gui);
     break;
     /************************************************************
              Fighting Related KeyStroke section
     /************************************************************/
        case TK_P://p 0
            fightDmg = player->getDmg(0);
            player->fight(map, gui, 0, fightDmg);
            break;
        case TK_K:// k 1
            fightDmg = player->getDmg(1);
            player->fight(map, gui, 1, fightDmg);
            break;
        case TK_B: //b 2
            fightDmg = player->getDmg(2);
            player->fight(map, gui, 2, fightDmg);
            break;
        case TK_S://3 s
            fightDmg = player->getDmg(3);
            player->fight(map, gui, 3, fightDmg);
            break;
            
        case TK_X:
           if (showingmap == true)
           {
             showingmap = false;
           } else {
             showingmap = true;
           }
           break;
      case TK_L:
            fightDmg = 100;
            msg = "You cast the unforgivable curse.";
            gui->gamelog.push_back(msg);
            gui->banner();
            player->fight(map, gui, 666, fightDmg);
            break;
    /*****************************************************************/        
     case TK_Q:
     terminal_close();
     exit(0);
  	 default: break;
  }
}

int main() {
  int k;
  int i;
  int x, y;
  int numMonst=0, randRm;
  bool myTurn = true;
  std::list<int> keystrokes;
  ent* player;
  ent* badGuy;
  Items* item;
  ai skyNet;
  Map map(140,36);
 //map.fov = true;
  Gui gui(6, 1, 140, 36, 160, 45); 
  map.genRect(11, 12);
  map.placeItems(8);
  player = new ent(map.spx, map.spy, "aT", '@', color_from_name("magenta"));
  map.badGuys.push_back(player);
  map.spawnMonsters(13);
  terminal_open();
  terminal_set("window: title='C++ Tutorial', size=160x45");
  terminal_set("input: filter=[keyboard, mouse];");
  terminal_setf("font: VeraMoBd.ttf, size=8x16;"),
  terminal_set("0xE100: Tiles.png, size=12x16, spacing=1x1;");
  terminal_set("0xF100: Tiles.png, size=32x32;");
  gui.drawGui(player, &map);
  drawAll(&map, player, 7); 
  terminal_refresh();
  while(true)
  {
  if (terminal_has_input()) {
   myTurn = true;  
   k = terminal_read();
   keystrokes.push_front(k);
   handle_keys(k, player, &map, &gui);
   //Logging key strokes.
   if (k == TK_BACKSPACE)
   {
     for (auto z : keystrokes)
     {
       std::cout<<z<<"\n";
     }
   }
  
  myTurn=false;
  }
 
  if (myTurn == false)
  {
    skyNet.moveMonsters(&map, &player->pos);
    myTurn = true;
  }
   
   terminal_clear(); 
   gui.drawGui(player, &map);
   drawAll(&map, player, 6);
   terminal_refresh();
  }
  terminal_close();
  return 0;
}
