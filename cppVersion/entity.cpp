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
ent::ent(int x, int y, int id, char ch, std::string name)
{
  Point N({0,-1,'^'});Point S({0,1,'v'});
  Point E({1,0,'>'});Point W({-1,0,'<'});
  cdir[0]=N; cdir[1]=E; cdir[2]=S; cdir[3]=W;
  this->pos.x = x;
  this->pos.y = y;
  this->id = id;
  this->ch[0] = ch;
  this->ch[1] = '\n';
  this-> name = name;
  health = 45;
  strength = 5;
  defence = 2;
  this->maxhealth = this->health;
  alive = true;
  pathfinding = true;
  freestep = 0;
  std::cout<<ch<<", an "<<name<<" has appeared, alive and confused. "<<id<<" "<<pos.x<<"/"<<pos.y<<"\n";
}

ent::~ent()
{
  std::cout<<"adios!"<<"\n";
}

void ent::die()
{
  std::string newname = "(DEAD) " + this->name;
  this->alive = false;
  this->ch[0] = 'D';
  this->health = 0;
  this->strength = 0;
  this->name = newname;
}

bool ent::move(dungeon* map, int dx, int dy, std::vector<ent*> goblins)
{
  Point newPos(this->pos.x+dx,this->pos.y+dy);
 if (canWalk(map, this->pos.x+dx, this->pos.y+dy))
 {
   for (auto gangster : goblins)
   {
     if (gangster->pos == newPos)
     {
       std::cout<<"oof\n";
     }
   }
  map->layout[pos.x][pos.y].blocks = false;
  map->layout[pos.x][pos.y].populated = false;
  this->pos.x += dx;
  this->pos.y += dy;
  map->layout[pos.x][pos.y].populated = true;
  map->layout[pos.x][pos.y].blocks = true;
 }
 if (isStairs(map))
 {
   return true;
 }
 return false;
}

bool ent::inBounds(Point* p)
{
  return 0 <= p->x && p->x < 100
       && 0 <= p->y && p->y < 45;
}

void ent::autostep(dungeon* map, Point target, ent* player)
{
  if (target == player->pos)
  {
    std::cout<<"Oof\n";
  } else 
  if (canWalk(map, target.x, target.y) && inBounds(&target)) 
  {
    
    map->layout[this->pos.x][this->pos.y].blocks = false;
    map->layout[this->pos.x][this->pos.y].populated = false;
    this->pos.x = target.x;
    this->pos.y = target.y;
    map->layout[target.x][target.y].populated = true;
    map->layout[target.x][target.y].blocks = true;
  }
}

void ent::dumbstep(dungeon* map, ent* player, Battle* deathmatch)
{
   Point playerPos = player->pos;
   int dx = playerPos.x - this->pos.x;
   int dy = playerPos.y - this->pos.y;
   int stepdx = (dx > 0 ? 1:-1);
   int stepdy = (dy > 0 ? 1:-1);
   float distance=sqrtf(dx*dx+dy*dy);
   if ( distance >= 2 ) {
       dx = (int)(round(dx/distance));
       dy = (int)(round(dy/distance));
       if (map->layout[this->pos.x+dx][this->pos.y+dy].blocks == false) {
           map->layout[this->pos.x][this->pos.y].blocks = false;
           this->pos.x += dx;
           this->pos.y += dy;
           map->layout[this->pos.x][this->pos.y].blocks = true;
       }
    } else {
      deathmatch->thunderDome(player, this);
    }
}

void ent::render()
{
 terminal_layer(3);
 color_t clearbk = 0x00;
 terminal_bkcolor(clearbk);
 if (this->id == 666)
 {
    terminal_color("green");
    terminal_print(pos.x+1,pos.y+1,"@");
 } else {
    if (this->alive == true)
    {
      terminal_color("flame");
      terminal_printf(pos.x+1, pos.y+1, "%c", this->ch[0]);
    } else {
      terminal_color("white");
      terminal_printf(pos.x+1,pos.y+1,"%c", this->ch[0]);
      terminal_layer(4);
      terminal_color("[darker] red");
      terminal_print(pos.x+1,pos.y+1, "X");
    }
 }
}

bool ent::canWalk(dungeon* map, int x, int y)
{
  if (map->layout[x][y].blocks == true) {
   return false;
  } else {
   return true;
  }
}

bool ent::isStairs(dungeon* map)
{
  if (this->pos.x == map->stairsDown.x && this->pos.y == map->stairsDown.y)
  {
    return true;
  }
  return false;
}

std::tuple<std::string, std::vector<item*>> ent::checkItem(std::vector<item*> booty)
{
  int cnt = 0;
  std::string itmName;
  std::tuple<std::string, std::vector<item*>> ret;
  std::vector<item*>::iterator item_it;
  item_it = booty.begin();
  for (auto itm : booty)
  {
    if (this->pos.x == itm->pos.x && this->pos.y == itm->pos.y)
    {
          itmName = itm->name;
          inventory.push_back(itm);
          booty.erase(item_it);
          break;
    } else {
    }
    item_it++;
    cnt++;
  }
  ret = std::make_tuple(itmName, booty);
  return ret;
}

bool ent::checkForEnemy(dungeon* themap, Point target)
{
  bFirst bf(themap);
  if (bf.bFS(this->pos, target, 3) == true)
  {
    return true;
  } else {
    return false;
  }
}