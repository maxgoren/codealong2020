  
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

void drawAll(Map*, ent*,int);

ent::ent(int x, int y, std::string name, char ch, color_t col)
{
 this->health = 100.00;
 this->dmgPow = 2;
 this->pos.x = x;
 this->pos.y = y;
 this->sym[0] = ch;
 this->sym[1] = '\0';
 this->col = col;
 this->name = name;
 if (name.compare("aT") == 0)
 {
   this->id = 420666;
 } else {
  this->id = getrand(666,3000) - 2 * 8 / 14;
 }
 std::cout<<"a star is born! "<<name<<"  "<<id<<"\n";
}

ent::~ent()
{
 std::cout<<"adios\n";
}

void ent::move(Map* map, int x, int y)
{
 if (map->layout[pos.x + x][pos.y + y].blocks == false)
 {
   map->layout[pos.x][pos.y].blocks = false;
   map->layout[pos.x][pos.y].populated = false;
   this->pos.x += x;
   this->pos.y += y;
   map->layout[pos.x][pos.y].populated = true;
   map->layout[pos.x][pos.y].blocks = true;
   if (map->fov == true) {
      map->layout[this->pos.x][this->pos.y].beenover = true;
   }
 }
}

void ent::render()
{
 if (this->id !=420666)
 {
 terminal_color(color_from_argb(255,0,0,255));
 terminal_print(pos.x, 10 + pos.y, sym);
 } else {
   terminal_color(color_from_argb(255,0,255,0));
   terminal_print(pos.x, 10 + pos.y, sym);
 }
}



double ent::getDmg(int method)
{
  double dmg;
  double done;
  std::cout<<"getdmg: "<<"\n";
  switch (method)
  {
    case 0:
        dmg = std::get<0>(this->attack.hurts.at(0));
        done = getrandfloat(dmg - this->dmgPow, dmg + this->dmgPow);
        break;
    case 1:
        dmg = std::get<0>(this->attack.hurts.at(1));
        done = getrandfloat(dmg - this->dmgPow, dmg + this->dmgPow);
        break;
    case 2:
        dmg = std::get<0>(this->attack.hurts.at(2));
        done = getrandfloat(dmg - this->dmgPow, dmg + this->dmgPow);
        break;
    case 3:
        dmg = std::get<0>(this->attack.hurts.at(3));
        done = getrandfloat(dmg - this->dmgPow, dmg + this->dmgPow);
        break;
    default:
        return 0;
  }
  std::cout<<done<<"\n";
  return done;
}



void ent::fight(Map* map, Gui* gui, int method, double dmg)
{
 int i;
 int rev;
 Point enemy;
 int enemyID;
 std::string msg;
 bool foundone = false;
 int x=this->pos.x;
 int y=this->pos.y;
 enemy.x = 0;
 enemy.y = 0;
 if (this->id == 420666)
 {
   for (auto g : map->badGuys)
   {
     if (g->id != 420666)
     {
      if (map->isInFov(g->pos.x,g->pos.y, this->pos.x, this->pos.y) < 3)
      {
        enemyID = g->id;
        enemy = g->pos;
        foundone = true;
        std::cout<<"ding"<<g->id<<"\n";
        break;
      }
     }
   }
 } else {
   for (auto p : map->badGuys)
   {
     if (p->id == 420666)
     {
       enemy = p->pos;
       foundone = true;
     }
   }
 }
 if (foundone == true)
 {
 i = 0;
 for (auto p  : map->badGuys)
 {
  if (enemyID == p->id)
  {
   p->health = p->health - dmg;
   if (p->id == this->id)
   {
     gui->gamelog.push_back("You recieve " + std::to_string(dmg) + " damage");
   } else {
    if (method == 666)
    {
        gui->gamelog.push_back("The " + p->name + " falls to the floor dead");
        this->battlesWon++;
        gui->drawGui(this, map);
        map->badGuys.erase(map->badGuys.begin()+ i);
        map->layout[enemy.x][enemy.y].populated = false;
        map->layout[enemy.x][enemy.y].blocks = false;
        return;
    }
   if (p->health <= 0)
   {
    gui->gamelog.push_back("Your" + std::get<1>(this->attack.hurts.at(method)) + " lands causing the " + p->name + "  to fall to the floor dead.");  
    this->battlesWon++;
    gui->drawGui(this, map);
    map->badGuys.erase(map->badGuys.begin()+ i);
    map->layout[enemy.x][enemy.y].populated = false;
    map->layout[enemy.x][enemy.y].blocks = false;
    return;
   } else {
    gui->gamelog.push_back("The " + p->name + " howls in rage from your " + std::get<1>(this->attack.hurts.at(method)) + "!");
    gui->gamelog.push_back(std::string(p->name + " recieves " + std::to_string(dmg) + "damage."));
    gui->banner();
    if (getrand(1,20) < 15)
    {
      rev = getrand(0,3);
      dmg = p->getDmg(rev);
      p->fight(map,gui,rev,dmg);
    }
    }
   }
   enemy.x = 0;
   enemy.y = 0;
    return;
   }
  i++;
 }
 } else {
 }
 enemy.x = 0;
 enemy.y = 0;
}




void ent::handleItem(Map* map, Gui* gui)
{
  std::string msg;
  int k;
  int cnt = 0;
  int selection;
  for (auto i : map->itemList)
  {
    if (this->pos == i->pos)
    {
      gui->gamelog.push_back("You found a " + i->name + "!\n");
      gui->banner();
      while (true) {
      if (terminal_has_input()) {  
      k = terminal_read();
      switch (k)
      {
        case TK_K:
          this->inventory.push_back(i);
          gui->gamelog.push_back(i->name + " was added to inventory");
          map->itemList.erase(map->itemList.begin() + cnt);
          return;
          break;
        case TK_U:
          selection = gui->itemMenu();
          break;  
      default:
         gui->gamelog.push_back("Eh, probably dont need it anyway..");
         gui->banner();
         return;
      }
      return;
      }
      gui->drawGui(this, map);
      drawAll(map, this, 2);
      terminal_refresh();
      }
    } else {
    }
    cnt++;
  }
}