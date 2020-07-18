  
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

Gui::Gui(int mx, int my, int mw, int mh, int sw, int sh)
{
 this->mapX = mx;
 this->mapY = my;
 this->mapW = mw;
 this->mapH - mh;
 this->scrW = sw;
 this->scrH = sh;
 this->GameTime.min = 0;
 this->GameTime.sec = 0;
 timeStart = std::chrono::high_resolution_clock::now();
 std::thread([&]
 { while (true) { std::this_thread::sleep_for(std::chrono::milliseconds(500));
    fetchTime();
    }}).detach();
}

void Gui::fetchTime()
{
   std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - timeStart;
  int hour = 0;
  int min = 0;
  int sec = 0;
  if (elapsed.count() > 60)
  {
    min = elapsed.count() / 60;
    sec = elapsed.count() - (60*min);
  } else {
    min = 0;
    sec = elapsed.count();
  }
  GameTime.min = min;
  GameTime.sec = sec;
}


void Gui::fade(int x,int y,int start[3],int fin[3], std::string message)
{
 int i;
 int sentSize;
 int stepping = message.length();
 int distance[3] = {(fin[0] - start[0])/stepping,
 		    (fin[1] - start[1])/stepping,
 		    (fin[2] - start[3])/stepping,};
 int color[3] = {start[0], start[1], start[2]};
 terminal_layer(3);
 for (i = 0; i < stepping; i++)
 {
  color[0] = color[0] + distance[0];
  color[1] = color[1] + distance[1];
  color[2] = color[2] + distance[2];
  terminal_color(color_from_argb(255, color[0], color[1], color[2]));
  terminal_print(x+i, y, message.c_str() + i);
 }
}
class greyBar {
  Point uL;
  Point lR;
  color_t mask;
  public:
  void moveUp();
  void moveDown();
  void render();
  greyBar(int x, int y);
  bool operator=(const  greyBar& other) const {
    return uL == other.uL && lR == other.lR;
  }
};

greyBar::greyBar(int x, int y)
{
  this->uL.x = x;
  this->uL.y = y;
  this->lR.x = x+14;
  this->lR.y = y + 1;
    this->mask = color_from_argb(200, 0xce, 0xce, 0xce);
    this->mask *= .86f;
  std::cout<<"greyBar alive, color:"<<this->mask<<" where?"<<uL.x<<lR.x<<"\n";
}

void greyBar::render()
{
  int sX, sY;
  for (sX = this->uL.x; sX < this->lR.x; sX++)
  {
      terminal_layer(0);
      terminal_bkcolor(this->mask);
      terminal_color(this->mask);
      terminal_print(sX,this->uL.y, " ");
  }
  terminal_refresh();
}
void greyBar::moveUp()
{
  terminal_layer(0);
  this->uL.y--;
  this->lR.y--;
  this->render();
}

void greyBar::moveDown()
{
  terminal_layer(0);
  this->uL.y++;
  this->lR.y++;
  this->render();
}

int Gui::itemMenu()
{
 int k;
 greyBar* b_bar;
 b_bar = new greyBar(mapW+3, 17); 
 b_bar->render();
  while (true)
  {
    if (terminal_has_input())
    {
     k = terminal_read();
     switch (k)
     {
       case TK_UP:
         b_bar->moveUp();
         break;
       case TK_DOWN:
         b_bar->moveDown();
         break;
        case TK_Q:
         return 0;
         break;
       default: break;
     }
    }
  }
}



void Gui::banner()
{
 std::string title = "C++ & BearLibTerminal Roguelike Tutorial!";
 int i;
 int x, y;
 int start[3] = {10,55,200};//{128,128,128};
 int fin[3] = {255,0,0};//{0,255,255};
 int sat=255;
 fade(scrW/2 - title.length()/2, 0, start, fin, title);
 std::vector<std::string>::iterator it;
 std::string messagebuff;
int m = 8; int l = 0;
if (gamelog.size() >= 1){
 for (auto i = gamelog.rbegin();  i < gamelog.rend(); i++)
 {
   messagebuff = *i;
   if (m - l > 1)
   {
   terminal_color(color_from_argb(sat,255,255,255));
   terminal_clear_area(3,m-l,40,1);
   terminal_printf(4, m - l, "%s", messagebuff.c_str());
   sat-=25;
   }
   l++;
 }
}
terminal_color("white");
terminal_print(4, 9, "Event log");
}



void Gui::healthBar(ent* player)
{
  double x, y;
  int cent = (((this->scrW -2) + (this->mapW+3)) / 2) - 5;
  double health_unit = 100 / ((this->scrW - 2) - (this->mapW+3));
  double health_amt = (player->health) / health_unit;
  int health_bar = (mapW + 3) + health_amt;
  terminal_layer(3);
  terminal_color("white");
  terminal_print(mapW+3, 12, "Health");
  terminal_printf(cent, 13, "%f\%", player->health);
  terminal_layer(0);
  terminal_bkcolor("red");
  for (x = this->mapW + 3; x < this->scrW - 2; x++)
  {
    terminal_print(x, 13, " ");
  }
  terminal_bkcolor("green");
  for (x = this->mapW+3; x < health_bar - 1; x++)
  {
    terminal_print(x, 13, " ");
  }

}

void Gui::timeInfo()
{
  int start[3] = {0, 255,0};
  int fin[3] = {11, 99, 187};
  fade(scrW-35, 2, start, fin, "Game Time:");
  terminal_layer(2);
  terminal_clear_area(scrW-37,3,10,1);
  terminal_color("white");
  if (this->GameTime.sec < 10)
  {
    terminal_printf(scrW-33, 3, "%d:0%d", this->GameTime.min, this->GameTime.sec);
  } else {
    terminal_printf(scrW-33, 3, "%d:%d", this->GameTime.min, this->GameTime.sec);
  }
}

void Gui::showInventory(ent* player, Map* map, std::map<std::string,std::string> box)
{
  int i = 0;
  int start[3] = {0,255,0};
  int fin[3] = {255, 0, 0};
  std::string msg = "Player Items";
  fade(mapW+3,18,start,fin,msg);

  terminal_color("red");                         //Item Inventory
  terminal_print(mapW+2, 17, box["uL"].c_str());
  terminal_print(scrW-2, 17, box["uR"].c_str());
  for (auto item : player->inventory)
  {
    terminal_printf(mapW+3, 19+i, "%d)%s %02f/%02f", i, item->name.c_str(), item->heals, item->powers);
    terminal_print(mapW+2, 18+i, box["side"].c_str());
    terminal_print(scrW-2, 18+i, box["side"].c_str());
    i++;
  }
  terminal_print(mapW+2, 19+i, box["lL"].c_str());
  terminal_print(scrW-2, 19+i, box["lR"].c_str());
  terminal_print(mapW+2, 18+i, box["side"].c_str());
  terminal_print(scrW-2, 18+i, box["side"].c_str());
  for (int x = mapW+3; x < scrW-2; x++)
  {
    terminal_print(x, 19+i, box["top"].c_str());
  }
}



void Gui::drawGui(ent* player, Map* map)
{
 int x, y;
 //Top five rows for banner/message log section
 terminal_layer(0); //we can set bgcolor on terminal_layer 0 to make a "frame"
 
 //GREY FRAMING
 for (x = 0; x < scrW; x++) {
  for (y = 0; y < scrH; y++) {  
   terminal_bkcolor("black");
    terminal_print(x, y, " ");
    terminal_bkcolor("#cecece");
    terminal_print(x, 0, " ");
    terminal_print(x, 10, " ");
    terminal_print(x, scrH, " "); 
   terminal_print(0, y, " ");
   terminal_print(mapW + 1, y+10, " ");
   terminal_print(scrW-1, y, " ");
 }
}

 std::map<std::string, std::string> box;
 box["uL"] =  "[U+250F]";
 box["lL"] = "[U+2517]";
 box["uR"] = "[U+2513]";
 box["lR"] = "[U+2518]";
 box["side"] = "[U+2503]";
 box["top"] = "[U+2501]";

 terminal_layer(2);
 terminal_color("red");
 terminal_print(2,1, box["uL"].c_str());       //this is the message log box.
 terminal_print(2,2, box["side"].c_str());
 terminal_print(2,3, box["side"].c_str());
 terminal_print(2,4, box["side"].c_str());
 terminal_print(2,5, box["side"].c_str());
 terminal_print(2,6, box["side"].c_str());
 terminal_print(2,7, box["side"].c_str());
 terminal_print(2,8, box["side"].c_str());
 terminal_print(2,9,  box["lL"].c_str());
 terminal_print(scrW-40,1, box["uR"].c_str());
 terminal_print(scrW-40,2, box["side"].c_str());
 terminal_print(scrW-40,3, box["side"].c_str());
 terminal_print(scrW-40,4, box["side"].c_str());
 terminal_print(scrW-40,5, box["side"].c_str());
 terminal_print(scrW-40,6, box["side"].c_str());
 terminal_print(scrW-40,7, box["side"].c_str());
 terminal_print(scrW-40,8, box["side"].c_str());
 terminal_print(scrW-40,9, box["lR"].c_str());
 terminal_layer(3);

 for (x = 3; x < scrW - 40; x++)
 {
  terminal_print(x,1, box["top"].c_str()); 
  terminal_print(x,9, box["top"].c_str());
 }
 
 terminal_color("red");
 terminal_print(mapW+2, 11, box["uL"].c_str());     //Health bar box
 terminal_print(scrW-2, 11, box["uR"].c_str());
 terminal_print(mapW+2, 12, box["side"].c_str());
 terminal_print(scrW-2, 12, box["side"].c_str());
 terminal_print(mapW+2, 13, box["side"].c_str());
 terminal_print(scrW-2, 13, box["side"].c_str());
 terminal_print(mapW+2, 14, box["lL"].c_str());
 terminal_print(scrW-2, 14, box["lR"].c_str());
 
 terminal_color("red");
 terminal_print(scrW-38, 1, box["uL"].c_str());     //elapsed Time.
 terminal_print(scrW-18, 1, box["uR"].c_str());
 terminal_print(scrW-38, 2, box["side"].c_str());
 terminal_print(scrW-18, 2, box["side"].c_str());
 terminal_print(scrW-38, 3, box["side"].c_str());
 terminal_print(scrW-18, 3, box["side"].c_str());
 terminal_print(scrW-38, 4, box["side"].c_str());
 terminal_print(scrW-18, 4, box["side"].c_str());
 terminal_print(scrW-38, 5, box["lL"].c_str());
 terminal_print(scrW-18, 5, box["lR"].c_str());
 for (x = scrW-37; x < scrW-18; x++)
 {
   terminal_print(x,1, box["top"].c_str());
   terminal_print(x,5, box["top"].c_str());
 }

 for (x = mapW+3; x < scrW-2; x++) {
   //terminal_print(x, 7, box["top"].c_str());
  // terminal_print(x, 10, box["top"].c_str());
   terminal_print(x, 11, box["top"].c_str());
   terminal_print(x, 14, box["top"].c_str());
   terminal_print(x, 17, box["top"].c_str());
 }
mouse.x = terminal_state(TK_MOUSE_X);
mouse.y = terminal_state(TK_MOUSE_Y) - 10;
terminal_layer(3);
terminal_print(scrW - 16, 2, "[u]Examine Info:[/u]");
terminal_printf(scrW-16, 3, "Mouse: %d/%d", mouse.x, mouse.y);
if (map->layout[mouse.x][mouse.y].populated == true) {
  for (auto m : map->badGuys)
  {
    if (m->pos == mouse)
    {
      terminal_printf(scrW-16, 4, "%s %d", m->name.c_str(), m->id);
    }
  }
  for (auto z : map->itemList)
  {
    if (z->pos == mouse) {
      terminal_printf(scrW-16, 4, "%s", z->name.c_str());
      terminal_printf(scrW-16, 6, "%f %f", z->powers, z->heals);
    }
  }
}
terminal_printf(scrW-16, 5, "Monsters: %d", map->badGuys.size() - 1);
//top panel
banner();
//side panels
healthBar(player);
timeInfo();
showInventory(player, map, box);
}
