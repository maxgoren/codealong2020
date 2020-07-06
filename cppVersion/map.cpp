
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



void Map::digRect(Rect room)
{
    int x, y;
    for (x = room.uL.x; x < room.lR.x; x++)
    {
	for (y = room.uL.y; y < room.lR.y; y++)
	{
	   this->layout[x][y].blocks = false;
	   this->layout[x][y].isinRoom = room.idNum;
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
 scrSect.push_back(scrSec1);

 Rect scrSec2(width/2, 1, width/2 - 1, height/2 - 1);
 scrSect.push_back(scrSec2);

 Rect scrSec3(1, height/2, width/2, height/2);
 scrSect.push_back(scrSec3);

 Rect scrSec4(width/2, height/2, width/2 - 1, height/2 - 1);
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
         layout[ax][ay].isinRoom = 77; //77 =pathway
      }
      std::cout<<"From: Y"<<start->cent.y<<" to "<<fin->cent.y<<"\n";
   } else {
      std::cout<<"if two, codition B\n";
      for (by = fin->cent.y; by <= start->cent.y; by++)
      {
        layout[bx][by].blocks = false;
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
    }
    for (by = fin->cent.y; by >= (start->cent.y + fin->cent.y) / 2; by--)
    {
        layout[fin->cent.x][by].blocks = false;
        layout[fin->cent.x][by].isinRoom = 77;
    }
  } else {
    std::cout<<"If one, condition B\n";
    for (ay = start->cent.y; ay >= (start->cent.y + fin->cent.y) / 2; ay--)
    {
      layout[start->cent.x][ay].blocks = false;
      layout[start->cent.x][ay].isinRoom = 77;
    }
    for (by = fin->cent.y; by <= (start->cent.y + fin->cent.y) / 2; by++)
    {
     layout[fin->cent.x][by].blocks = false;
     layout[fin->cent.x][by].isinRoom = 77;
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
  }
 }
}

void Map::spawnMonsters(int numBads)
{
 ent* badGuy;
 int i, randRm, x, y;
 for (i = 0; i < numBads; i++)
 {
  randRm = getrand(0, rooms.size() - 1);
  if (rooms[randRm].numEnts <= 2)
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
     badGuys.push_back(*badGuy);
     rooms[randRm].numEnts++;
     layout[x][y].populated = true;
     layout[x][y].blocks = true;
   }
  }
}
}
