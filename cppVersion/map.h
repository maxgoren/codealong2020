#include <vector>
#include "BearLibTerminal.h"

int getrand(int min, int max)
{
  return (rand() % (max - min + 1)) + min;
}

struct Tile {
    bool blocking;
    Tile() : blocking(true) {}
};

class Rect {
public:
    int x1, x2;
    int y1, y2;
    int w, h;
    int centx, centy;
    bool collision(Rect otro);
    Rect(int,int,int,int);
};

Rect::Rect(int x, int y, int w, int h)
{
    x1 = x;
    y1 = y;
    x2 = x1 + w;
    y2 = y1 + h;
    centx = (x1 + x2) / 2;
    centy = (y1 + y2) / 2;
}


bool Rect::collision(Rect otro)
{
  if (x1 <= otro.x2 && x2 >= otro.x1 &&
      y1 <= otro.y2 && y2 >= otro.y1)
      {
          return true;
          std::cout<<"COLLISION!\n";
      }
   return false;
}

class gameMap {
public:
    int mw;
    int mh;
    int mxRmsz = 8;
    int mnRmsz = 5;
    std::vector<Rect> rooms;
    
    gameMap(int w, int h);
    bool isBlocked(int x, int y) const;
    void draw();
protected:
    Tile tiles[80][40];
    void makeRoom(Rect room);
    void vtunnel(int y1, int y2, int x);
    void htunnel(int x1, int x2, int y);
    void makeMap();
    Rect rectToTry(Rect room);
    
};


gameMap::gameMap(int w, int h)
{
    mw = w;
    mh = h;
    rooms.assign(0, Rect(1,1,1,1));
    rooms.clear();
    makeMap();
}

bool gameMap::isBlocked(int x, int y) const
{
    return tiles[x][y].blocking;
}

void gameMap::vtunnel(int y1, int y2, int x)
{
    int i;
    std::cout<<"Tunnel down from"<<y1<<" to "<<y2<<std::endl;
    if (y1 < y2 +1)
    {
        for (i = y1; i < y2 +1; i++)
        {
            tiles[x][i].blocking = false;
            std::cout<<"Dig";
        }
    } else {
        for (i = y2 + 1; i < y1; i++)
        {
            tiles[x][i].blocking = false;
            std::cout<<"dug";
        }
    }
}
void gameMap::htunnel(int x1, int x2, int y)
{
    int i;
    if (x1 < x2 +1)
    {
        for (i = x1; i < x2 +1; i++)
        {
            tiles[i][y].blocking = false;
        }
    } else {
        for (i = x2 + 1; i < x1; i++)
        {
            tiles[i][y].blocking = false;
        }
    }
}

void gameMap::makeRoom(Rect room)
{
    int x, y;
    if (room.x1 < room.x2)
    {
      for (x = room.x1; x < room.x2; x++)
      {
        for (y = room.y1; y < room.y2; y++)
        {
            tiles[x][y].blocking = false;

        }
      }
    } else {
        int tmp;
        tmp = room.x1;
        room.x1 = room.x2;
        room.x2 = tmp;
        if (room.y1 < room.y2)
        {
          makeRoom(room);
        } else {
            int tmp2;
            tmp2 = room.y1;
            room.y1 = room.y2;  //boy, whachu know 'bout recursion?
            room.y2 = tmp2;
            makeRoom(room);
        }
    }

}
Rect gameMap::rectToTry(Rect room)
{
    room.w = getrand(mnRmsz, mxRmsz);
    room.h = getrand(mnRmsz, mxRmsz);
    room.x1 = getrand(1, mw);
    room.y1 = getrand(1, mh);
    room.x2 = room.x1 + room.w;
    room.y2 = room.y1 + room.h;
    return room;
}

void gameMap::makeMap()
{
    int r, numRooms = 0;
    int otros = 0;
    int maxRooms = 30;
    int prevX, prevY;
    int newX, newY;
    Rect room(1,1,1,1);
    for(r = 0; r < maxRooms; r++)
    {
        room = rectToTry(room);
        if (numRooms == 0) { 
            std::cout<<"vec size:"<<rooms.size()<<std::endl;
            makeRoom(room);rooms.push_back(room); numRooms++; 
            std::cout<<"vec size: "<<rooms.size()<<std::endl;
        }
            newX = room.x1 + room.x2 / 2;
            newY = room.y1 + room.y2 / 2;
            if (numRooms > 0) {
                prevX = rooms[r - 1].x1 + rooms[r - 1].x2 / 2;
                prevY = rooms[r - 1].y1 + rooms[r - 1].y2 / 2;
                if (getrand(1, 2) == 1)
                {
                    htunnel(prevX, newX, prevY);
                    vtunnel(prevY, newY, newX);
                } else {
                    vtunnel(prevY, newY, prevX);
                    htunnel(prevX, newX, newY);
                }
            }
            makeRoom(room);
            rooms.push_back(room);  
            numRooms++;
            std::cout<<"BZZZT\n";
            room = rectToTry(room);

    }
    for (r = 0; r < numRooms; r++)
    {
        std::cout<<"Room number "<<r<<" @ "<<rooms[r].x1<<" : "<<rooms[r].y1<<" / "<<rooms[r].x2<<" : "<<rooms[r].y2<<std::endl;
    }
}

void gameMap::draw()
{
    int x, y;
    terminal_layer(0);
    for (x = 0; x < 75; x++)
    {
        for (y = 5; y <40; y++)
        {
            if (isBlocked(x,y))
            {
                terminal_color("white");
                terminal_print(x, y, "o");

            } else {
                terminal_color("red");
                terminal_print(x, y, ".");
            } 
        }
    }
    terminal_refresh();
    terminal_layer(1);
}