


void dungeon::conRoomStyle1(std::vector<Room*> path)
{
  int ax,bx;
  int ay,by;
  int x, y, w , h;
  Room* start;
  Room* fin;
  Room* tunnelA;
  Room* tunnelB;
  int i = 0;
  int r;
  
  std::cout<<"c1 "<<path.size()<<std::endl;
  std::cout<<"------------------------------------------\n";
  for ( r = 0; r < path.size() - 1; r++)
  {
   start = path[i]->getRoom();
   fin = path[i+1]->getRoom();
   std::cout<<"Connecting: "<<start->id<<" to "<<fin->id<<"\n";
   if (start->cent.x <= fin->cent.x)
   {
      x = start->cent.x;
      y = start->cent.y;
      w = (fin->cent.x + start->cent.x) / 2;
      tunnelA = new Room(x, y, w, 1, 77);
      if (passCheck(tunnelA))
        halls.push_back(tunnelA);

      x = fin->cent.x;
      y = fin->cent.y;
      w = (fin->cent.x + start->cent.x) / 2;
      tunnelB = new Room(x, y, w, 1, 77);
      if (passCheck(tunnelB))
        halls.push_back(tunnelB);

      std::cout<<"From: X: "<<x<<" to "<<w<<" length: "<<w - x<<"\n";
      std::cout<<"From: x: "<<start->cent.x<<" to "<<w<<" length: "<<w-start->cent.x<<"\n";
   }

      x = (fin->cent.x + start->cent.x) / 2;
      y = start->cent.y;
      h = fin->cent.y - start->cent.y;
      tunnelA = new Room(x,y,2,h,77);
      if (passCheck(tunnelA))
         halls.push_back(tunnelA);
      std::cout<<"From: Y"<<start->cent.y<<" to "<<fin->cent.y<<" "<<h<<" long.\n";
   
    std::cout<<"Connected.\n";
    i++;
  }
  std::cout<<"------------------------------------------\n";

}

void dungeon::conRoomStyle2(std::vector<Room*> path)
{
 int x, y;
 int w, h;
 int ax, ay;
 int bx, by;
 Room* start;
 Room* fin;
 Room* tunnelA;
 Room* tunnelB;
 int r, i=0;
 std::cout<<"c2 "<<path.size()<<std::endl;
 std::cout<<"------------------------------------------\n";
 for (r = 0; r < path.size() - 1; r++)
 {
    start = path[i]->getRoom();
    fin   = path[i + 1]->getRoom();
    std::cout<<"Connecting: "<<start->id<<" to "<<fin->id<<"\n";

    x = start->cent.x;
    y = start->cent.y;
    h = (start->cent.y + fin->cent.y)/2;

    tunnelA = new Room(x, y, 1, h, 77);
    x = fin->cent.x;
    y = fin->cent.y;
    h = (start->cent.y + fin->cent.y) / 2;

    tunnelB = new Room(x,y,1,h, 77);
   if (passCheck(tunnelA))
   {     
        std::cout<<" Y: "<<tunnelA->y<<" X: "<<x<<" to: Y: "<<tunnelA->lR.y<<" length: "<<tunnelA->lR.y - tunnelA->uL.y<<std::endl;
        halls.push_back(tunnelA);
    }
    if (passCheck(tunnelB))
    {
        std::cout<<" Y: "<<tunnelB->y<<" X: "<<x<<" to: Y: "<<tunnelB->lR.y<<" length: "<<tunnelB->lR.y - tunnelB->uL.y<<std::endl;
        halls.push_back(tunnelB);
    }

/**********************************************************/

   x = start->cent.x;
   y = start->cent.y;
   w = (fin->cent.x + start->cent.x)/2;
   tunnelA = new Room(x,y,w,1, 77);

   x = fin->cent.x;
   y = fin->cent.y;
   w = (start->cent.x + fin->cent.x) /2;
   tunnelB = new Room(x,y,w,1, 77);
   
   if (passCheck(tunnelA))
   {
        std::cout<<" Y: "<<tunnelA->y<<" X: "<<tunnelA->x<<" to: X: "<<tunnelA->lR.x<<" ("<<tunnelA->w<<") length: "<<tunnelA->h - tunnelA->w<<std::endl;
        halls.push_back(tunnelA);
   }

   if (passCheck(tunnelB))
   {
        std::cout<<" Y: "<<tunnelB->y<<" X: "<<tunnelB->x<<" to: X: "<<tunnelB->lR.x<<"("<<w<<" )length: "<<tunnelB->h - tunnelB->w<<std::endl;
        halls.push_back(tunnelB);
   }
  
  std::cout<<"Connections complete.\n";
  i++;
 }
 std::cout<<"------------------------------------------\n";
}

void dungeon::crNB1(std::vector<Room*> rooms)
{
  int ax,bx;
  int ay,by;
  Room* start;
  Room* fin;
  int i = 0;
  int r;
  for ( r = 0; r < rooms.size() - 1; r++)
  {
   start = rooms[i];
   fin = rooms[i+1];
   std::cout<<"Connecting: "<<start->id<<" to "<<fin->id<<"\n";
   if (start->cent.x <= fin->cent.x)
   {
      std::cout<<"if one, condition A\n";
      for (ax = start->cent.x; ax <= (fin->cent.x + start->cent.x) / 2; ax++)
      {
	layout[ax][start->cent.y].blocks = false;
      	layout[ax][start->cent.y].level = 77;
      }
      for (bx = fin->cent.x; bx >= (fin->cent.x + start->cent.x) / 2; bx--)
      {
        layout[bx][fin->cent.y].blocks = false;
        layout[bx][fin->cent.y].level = 77;
      }
      std::cout<<"From: X"<<start->cent.x<<" and "<<fin->cent.x<<" to "<<(start->cent.x + fin->cent.x)/2<<"\n";
   } else {
      std::cout<<"If one condition B\n";
      for (ax = start->cent.x; ax >= (fin->cent.x + start->cent.x) / 2; ax--)
      {
        layout[ax][start->cent.y].blocks = false;
        layout[ax][start->cent.y].level = 77;
      }
      for (bx = fin->cent.x; bx <= (fin->cent.x + start->cent.x) / 2; bx++)
      {
        layout[bx][fin->cent.y].blocks = false;
        layout[bx][fin->cent.y].level = 77;
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
         layout[ax][ay].level = 77; //77 =pathway
      }
      std::cout<<"From: Y"<<start->cent.y<<" to "<<fin->cent.y<<"\n";
   } else {
      std::cout<<"if two, codition B\n";
      for (by = fin->cent.y; by <= start->cent.y; by++)
      {
        layout[bx][by].blocks = false;
        layout[bx-1][by].blocks = false;
        layout[bx][by].level = 77;
      }   
      std::cout<<"From: Y"<<fin->cent.y<<" to "<<start->cent.y<<"\n";
   }
  std::cout<<"Connected.\n";
  i++;
  }

}

void dungeon::crNB2(std::vector<Room*> rooms)
{
 int x, y;
 int ax, ay;
 int bx, by;
 Room* start;
 Room* fin;
 int r, i=0;
 for (r = 0; r < rooms.size() - 1; r++)
 {
  start = rooms[i];
  fin = rooms[i + 1];
   std::cout<<"Connecting: "<<start->id<<" to "<<fin->id<<"\n";
  if (start->cent.y <= fin->cent.y)
  {
    std::cout<<"If one, condition A\n";
    for (ay = start->cent.y; ay <= (start->cent.y + fin->cent.y) / 2; ay++)
    {
   	layout[start->cent.x][ay].blocks = false;
   	layout[start->cent.x][ay].level = 77;
     /***********************************/
     layout[start->cent.x+1][ay].blocks=false;
    }
    for (by = fin->cent.y; by >= (start->cent.y + fin->cent.y) / 2; by--)
    {
        layout[fin->cent.x][by].blocks = false;
        layout[fin->cent.x][by].level = 77;
        /**************************************/
        layout[fin->cent.x-1][by].blocks=false;
    }
  } else {
    std::cout<<"If one, condition B\n";
    for (ay = start->cent.y; ay >= (start->cent.y + fin->cent.y) / 2; ay--)
    {
      layout[start->cent.x][ay].blocks = false;
      layout[start->cent.x][ay].level = 77;
      /***************************************/
      layout[start->cent.x-1][ay].blocks = false;
    }
    for (by = fin->cent.y; by <= (start->cent.y + fin->cent.y) / 2; by++)
    {
     layout[fin->cent.x][by].blocks = false;
     layout[fin->cent.x][by].level = 77;
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
     layout[ax][ay].level = 77;
   }
  } else {
   std::cout<<"If two, condition B\n";
   for (bx = fin->cent.x; bx <= start->cent.x; bx++)
   {
     layout[bx][by].blocks = false;
     layout[bx][by].level = 77;
   }
  }
  std::cout<<"Connection complete.\n";
  i++;
 }
}