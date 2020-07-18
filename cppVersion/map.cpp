
  
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



Rect::Rect(int x, int y, int w, int h)
{
 this->uL.x = x;
 this->uL.y = y;
 this->lR.x = x + w;
 this->lR.y = y + h;
}

Rect::Rect()
{

}

Map::Map(int w, int h)
{
 int x, y;
 this->width = w;
 this->height = h;
 //initialize tile grid
  for (x = 1; x < w - 1; x++)
  {
   for (y = 1; y < h - 1; y++)
   {
    layout[x][y].blocks = true;
    layout[x][y].pos.x = x;
    layout[x][y].pos.y = y;
   }
 }
}

bool Rect::collision(Rect other)
{
 if ((uL.x < other.lR.x) && (lR.x > other.uL.x) &&
     (uL.y < other.lR.y) && (lR.y > other.uL.y)) {
     return true; //collision
  } else {
  return false;
 }
}

double Map::isInFov(int x, int y, int px, int py)
{
    double alpha = (px - x) * (px - x);
    double beta = (py - y) * (py - y);
    return sqrt((alpha+beta)*1.0);
}


void Map::digRect(Rect room)
{
    int x, y;
    for (x = room.uL.x; x < room.lR.x; x++)
    {
	    for (y = room.uL.y; y < room.lR.y; y++)
	    {
	      this->layout[x][y].blocks = false;
	      this->layout[x][y].isinRoom = room.idNum;
        this->layout[x][y].value = 10;
	    }
    }
   std::cout<<"Dug room "<<room.idNum<<"from x"<<room.uL.x<<" to x "<<room.lR.x<<" and y"<<room.uL.y<<" to "<<room.lR.y<<".\n";
}

void Map::genRect(int numRoom, int maxSize)
{
 int i;
 int posx, posy, possize;
 int roomsMade = 0;
 int collisions = 0;
 Rect* posroom;
 //screensections;
 Rect scrSec1(1,1,width/2, height/2 - 1);
 scrSec1.numItems = 0;
 scrSec1.numEnts = 0;
 scrSect.push_back(scrSec1);
 Rect scrSec2(width/2, 1, width/2 - 1, height/2 - 1);
 scrSec2.numItems = 0;
 scrSec2.numEnts = 0;
 scrSect.push_back(scrSec2);
 Rect scrSec3(1, height/2, width/2, height/2);
 scrSec3.numItems = 0;
 scrSec3.numEnts = 0;
 scrSect.push_back(scrSec3);
 Rect scrSec4(width/2, height/2, width/2 - 1, height/2 - 1);
 scrSec4.numItems = 0;
 scrSec4.numEnts = 0;
 scrSect.push_back(scrSec4);
 
 std::cout<<"Screen partition complete.\n";
 while (roomsMade < numRoom)
 {
  possize = getrand(5, maxSize);
  switch (getrand(1,4))
  {
      case 1:
   	posx = getrand(scrSect[0].uL.x + 1, scrSect[0].lR.x - (possize + 1));
   	posy = getrand(scrSect[0].uL.y + 1, scrSect[0].lR.y - (possize + 1));
      	std::cout<<"Room: "<<roomsMade<<" section one selected\n";
      break;
      case 2:
   	posx = getrand(scrSect[1].uL.x + 1, scrSect[1].lR.x - (possize + 1));
   	posy = getrand(scrSect[1].uL.y + 1, scrSect[1].lR.y - (possize + 1));
        std::cout<<"Room: "<<roomsMade<<" section two selected\n";
      break;
      case 3:
	posx = getrand(scrSect[2].uL.x + 1, scrSect[2].lR.x - (possize + 1));
	posy = getrand(scrSect[2].uL.y + 1, scrSect[2].lR.y - (possize + 1));
        std::cout<<"Room: "<<roomsMade<<" section three selected\n";
      break;
      case 4:
	posx = getrand(scrSect[3].uL.x + 1, scrSect[3].lR.x - (possize + 1));
  	posy = getrand(scrSect[3].uL.y + 1, scrSect[3].lR.y - (possize + 1));
        std::cout<<"Room: "<<roomsMade<<" section four selected\n";
      break;
  }
  std::cout<<"Room: "<<roomsMade<<" posx/posy: "<<posx<<"/"<<posy<<"\n";
  posroom = new Rect(posx, posy, possize + (possize/2) , possize);
  posroom->idNum = roomsMade;
  std::cout<<"Room: "<<roomsMade<<" object created\n";
  posroom->cent.x = (posroom->uL.x + posroom->lR.x) / 2;
  posroom->cent.y = (posroom->uL.y + posroom->lR.y) / 2;
  std::cout<<"Room: "<<roomsMade<<" centx/y set: "<<posroom->cent.x<<"/"<<posroom->cent.y<<"\n";
  if (roomsMade > 0)
  {
     for (auto R = rooms.begin() ; R != rooms.end(); R++)
     { if (posroom->collision(*R)) { collisions++; } }
     if (collisions == 0)
     {
       digRect(*posroom);
       rooms.push_back(*posroom);
       roomsMade++;
       collisions = 0;
       std::cout<<"Room "<<posroom->idNum<<"made. x/y: "<<posroom->uL.x<<"/"<<posroom->uL.y<<" x2/y2:"<<posroom->lR.x<<"/"<<posroom->lR.y<<std::endl;
     } else {
       std::cout<<collisions<<"Collisions Detected.\n";
       collisions = 0;
     }
   } else {
     
     digRect(*posroom);
     rooms.push_back(*posroom);
     roomsMade++;
  }
  if (roomsMade == 2)
  {
   spy = rooms.at(0).cent.y;
   spx = rooms.at(0).cent.x;
  }
 }

  if (getrand(1,100) > 50)
   {
     connectRooms(rooms);
   } else {
     connectRooms2(rooms);
   }
 //placePortal();
 outline();
}

void Map::connectRooms(std::vector<Rect> rooms)
{
  int ax,bx;
  int ay,by;
  Rect* start;
  Rect* fin;
  int i = 0;
  int r;
  for ( r = 0; r < rooms.size() - 1; r++)
  {
   start = &rooms[i];
   fin = &rooms[i+1];
   std::cout<<"Connecting: "<<start->idNum<<" to "<<fin->idNum<<"\n";
   if (start->cent.x <= fin->cent.x)
   {
      std::cout<<"if one, condition A\n";
      for (ax = start->cent.x; ax <= (fin->cent.x + start->cent.x) / 2; ax++)
      {
	layout[ax][start->cent.y].blocks = false;
      	layout[ax][start->cent.y].isinRoom = 77;
      }
      for (bx = fin->cent.x; bx >= (fin->cent.x + start->cent.x) / 2; bx--)
      {
        layout[bx][fin->cent.y].blocks = false;
        layout[bx][fin->cent.y].isinRoom = 77;
      }
      std::cout<<"From: X"<<start->cent.x<<" and "<<fin->cent.x<<" to "<<(start->cent.x + fin->cent.x)/2<<"\n";
   } else {
      std::cout<<"If one condition B\n";
      for (ax = start->cent.x; ax >= (fin->cent.x + start->cent.x) / 2; ax--)
      {
        layout[ax][start->cent.y].blocks = false;
        layout[ax][start->cent.y].isinRoom = 77;
      }
      for (bx = fin->cent.x; bx <= (fin->cent.x + start->cent.x) / 2; bx++)
      {
        layout[bx][fin->cent.y].blocks = false;
        layout[bx][fin->cent.y].isinRoom = 77;
      }
      std::cout<<"From: X"<<start->cent.x<<" and "<<fin->cent.x<<" to "<<(start->cent.x + fin->cent.x)/2<<"\n";
   }
   if (start->cent.y <= fin->cent.y)
   {
      std::cout<<"if two condition A\n";
      for (ay = start->cent.y; ay <  fin->cent.y; ay++)
      {
         layout[ax][ay].blocks = false;
         layout[ax+1][ay].blocks = false;
         layout[ax][ay].isinRoom = 77; //77 =pathway
      }
      std::cout<<"From: Y"<<start->cent.y<<" to "<<fin->cent.y<<"\n";
   } else {
      std::cout<<"if two, codition B\n";
      for (by = fin->cent.y; by <= start->cent.y; by++)
      {
        layout[bx][by].blocks = false;
        layout[bx-1][by].blocks = false;
        layout[bx][by].isinRoom = 77;
      }   
      std::cout<<"From: Y"<<fin->cent.y<<" to "<<start->cent.y<<"\n";
   }
  std::cout<<"Connected.\n";
  i++;
  }

}

void Map::connectRooms2(std::vector<Rect> rooms)
{
 int ax, ay;
 int bx, by;
 Rect* start;
 Rect* fin;
 int r, i=0;
 for (r = 0; r < rooms.size() - 1; r++)
 {
  start = &rooms[i];
  fin = &rooms[i] + 1;
   std::cout<<"Connecting: "<<start->idNum<<" to "<<fin->idNum<<"\n";
  if (start->cent.y <= fin->cent.y)
  {
    std::cout<<"If one, condition A\n";
    for (ay = start->cent.y; ay <= (start->cent.y + fin->cent.y) / 2; ay++)
    {
   	layout[start->cent.x][ay].blocks = false;
   	layout[start->cent.x][ay].isinRoom = 77;
     /***********************************/
     layout[start->cent.x+1][ay].blocks=false;
    }
    for (by = fin->cent.y; by >= (start->cent.y + fin->cent.y) / 2; by--)
    {
        layout[fin->cent.x][by].blocks = false;
        layout[fin->cent.x][by].isinRoom = 77;
        /**************************************/
        layout[fin->cent.x-1][by].blocks=false;
    }
  } else {
    std::cout<<"If one, condition B\n";
    for (ay = start->cent.y; ay >= (start->cent.y + fin->cent.y) / 2; ay--)
    {
      layout[start->cent.x][ay].blocks = false;
      layout[start->cent.x][ay].isinRoom = 77;
      /***************************************/
      layout[start->cent.x-1][ay].blocks = false;
    }
    for (by = fin->cent.y; by <= (start->cent.y + fin->cent.y) / 2; by++)
    {
     layout[fin->cent.x][by].blocks = false;
     layout[fin->cent.x][by].isinRoom = 77;
     /***************************************/
     layout[fin->cent.x+1][by].blocks=false;
    }
  }
  if (start->cent.x <= fin->cent.x)
  {
    std::cout<<"If two, condition A\n";
   for (ax = start->cent.x; ax <= fin->cent.x; ax++)
   {
     layout[ax][ay].blocks = false;
     layout[ax][ay].isinRoom = 77;
   }
  } else {
   std::cout<<"If two, condition B\n";
   for (bx = fin->cent.x; bx <= start->cent.x; bx++)
   {
     layout[bx][by].blocks = false;
     layout[bx][by].isinRoom = 77;
   }
  }
  std::cout<<"Connection complete.\n";
  i++;
 }
}

void Map::connectR2R(Rect st, Rect fi)
{
 int ax, ay;
 int bx, by;
 Rect* start = &st;
 Rect* fin = &fi;
 int r, i=0;

  std::cout<<"Connecting: "<<start->idNum<<" to "<<fin->idNum<<"\n";
  if (start->cent.y <= fin->cent.y)
  {
    std::cout<<"If one, condition A\n";
    for (ay = start->cent.y; ay <= (start->cent.y + fin->cent.y) / 2; ay++)
    {
   	layout[start->cent.x][ay].blocks = false;
   	layout[start->cent.x][ay].isinRoom = 77;
     /***********************************/
     layout[start->cent.x+1][ay].blocks=false;
    }
    for (by = fin->cent.y; by >= (start->cent.y + fin->cent.y) / 2; by--)
    {
        layout[fin->cent.x][by].blocks = false;
        layout[fin->cent.x][by].isinRoom = 77;
        /**************************************/
        layout[fin->cent.x-1][by].blocks=false;
    }
  } else {
    std::cout<<"If one, condition B\n";
    for (ay = start->cent.y; ay >= (start->cent.y + fin->cent.y) / 2; ay--)
    {
      layout[start->cent.x][ay].blocks = false;
      layout[start->cent.x][ay].isinRoom = 77;
      /***************************************/
      layout[start->cent.x-1][ay].blocks = false;
    }
    for (by = fin->cent.y; by <= (start->cent.y + fin->cent.y) / 2; by++)
    {
     layout[fin->cent.x][by].blocks = false;
     layout[fin->cent.x][by].isinRoom = 77;
     /***************************************/
     layout[fin->cent.x+1][by].blocks=false;
    }
  }
  if (start->cent.x <= fin->cent.x)
  {
    std::cout<<"If two, condition A\n";
   for (ax = start->cent.x; ax <= fin->cent.x; ax++)
   {
     layout[ax][ay].blocks = false;
     layout[ax][ay].isinRoom = 77;
   }
  } else {
   std::cout<<"If two, condition B\n";
   for (bx = fin->cent.x; bx <= start->cent.x; bx++)
   {
     layout[bx][by].blocks = false;
     layout[bx][by].isinRoom = 77;
   }
  }
  std::cout<<"Connection complete.\n";
}

void Map::outline()
{
 int x, y;
 for (x = 0; x < width; x++)
 {
  for (y = 0; y < height; y++)
  {
    if (layout[x][y].blocks == false && layout[x+1][y].blocks == true)
    {
     layout[x+1][y].border = true;
    }
    if (layout[x][y].blocks == false && layout[x][y+1].blocks == true)
    {
     layout[x][y+1].border = true;
    }
    if (layout[x][y].blocks == false && layout[x-1][y].blocks == true)
    {
     layout[x-1][y].border = true;
    }
    if (layout[x][y].blocks == false && layout[x][y-1].blocks == true)
    {
     layout[x][y-1].border = true;
    }
    if (layout[x][y].blocks == false && layout[x-1][y].border == true && layout[x][y+1].border==true)
    {
      layout[x-1][y+1].border=true;
    }
    if (layout[x][y].blocks == false && layout[x-1][y].border == true && layout[x][y-1].border==true)
    {
      layout[x-1][y-1].border=true;
    }
    if (layout[x][y].blocks == false && layout[x+1][y].border == true && layout[x][y-1].border==true)
    {
      layout[x+1][y-1].border=true;
    }
    if (layout[x][y].blocks == false && layout[x+1][y].border == true && layout[x][y+1].border==true)
    {
      layout[x+1][y+1].border=true;
    }
  }
 }
}

void Map::spawnMonsters(int numBads)
{
 ent *badGuy;
 int numMonst = 0;
 int i, randRm, x, y;
 while (numMonst < 13)
 {
  randRm = getrand(0, rooms.size() - 1); 
  if (rooms.at(randRm).numEnts <= 2)
  {
    x = getrand(rooms[randRm].uL.x+1, rooms[randRm].lR.x-1);
    y = getrand(rooms[randRm].uL.y+1, rooms[randRm].lR.y-1);
    if (layout[x][y].populated == false && layout[x][y].blocks==false)
    {
     if (getrand(0,50) < 35)
     {
       badGuy = new ent(x, y, "Goblin", 'G', color_from_name("green"));
     } else {
       badGuy = new ent(x, y, "Vampire", 'V', color_from_name("flame"));
     }
     badGuys.push_back(badGuy);
     rooms[randRm].numEnts++;
     layout[x][y].populated = true;
     layout[x][y].blocks = true;
     numMonst++;
   }
  }
 }
}


void Map::placeItems(int numItems)
{
  int sect;
  int rit;
  float rp, rh;
  int itemsMade = 0;
  Point randPos;
  Items* item;
  struct stuff things;
    while (itemsMade < numItems)
    {
       rp = getrandfloat(0.10, 2.25);
       rh = getrandfloat(4.35, 9.33);
       rit = getrand(0,22);
      sect = getrand(0, 3);
      if (scrSect[sect].numItems < numItems)
      {
        randPos.x = getrand(this->scrSect.at(sect).uL.x, this->scrSect.at(sect).lR.x);
        randPos.y = getrand(this->scrSect.at(sect).uL.y, this->scrSect.at(sect).lR.y);
        if (this->layout[randPos.x][randPos.y].blocks == false && this->layout[randPos.x][randPos.y].populated == false)
        {
          item = new Items(randPos.x,randPos.y, things.things[rit], rh, rp);
          this->itemList.push_back(item);
          this->layout[randPos.x][randPos.y].populated = true;
          itemsMade++;
          scrSect[sect].numItems++;
        }
      }
    }
}

void Map::placePortal()
{
  int dx, dy;
  int dx2, dy2;
  int distance;
  int distance2;
  float dist;
  std::pair<Rect*,Rect*> closest;
  Rect far = rooms.back();
  Rect* start = &rooms.front();
  Rect* next;
  
  for (auto r = rooms.begin() + 1; r != rooms.end(); r++)
  {
    dx = r->cent.x - start->cent.x;
    dy = r->cent.y - start->cent.y;
    dx2 = r->cent.x - far.cent.x;
    dy2 = r->cent.y - far.cent.y;
    dist = sqrtf(dx*dx+dy*dy);
    distance = (int)round(dist);
    dist = sqrtf(dx2*dx2+dy2*dy2);
    distance2 = (int)round(dist);
    std::cout<<r->idNum<<" & "<<start->idNum<<"\n";
    std::cout<<"r -> start "<<distance<<"\n";
    std::cout<<r->idNum<<" & "<<far.idNum<<"\n";
    std::cout<<"r -> finnish "<<distance2<<"\n";
    if (distance < distance2)
    {
      next = start;
    } else {
      next = &far;
      far = *r;
    }
    std::cout<<"winner: "<<r->idNum<<" & "<<next->idNum<<"\n";
  }
  connectR2R(*start,*next);
  start = next;
}
