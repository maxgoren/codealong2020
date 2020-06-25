#include "map.h"
#include "helpers.h"
#include <iostream>

Rect::Rect(int x, int y, int w, int h)
{
    x1 = x;
    y1 = y;
    x2 = x + w;
    y2 = y + h;
    cx = (x1 + x2) / 2;
    cy = (y1 + y2) / 2;
}

bool Rect::collides(Rect other)
{
    if (x1 <= other.x1 && x1 >= other.x1 &&
        y1 <= other.y2 && y2 >= other.y1) {
            return true;
        } else {
            return false;
        }
}

Map::Map(int mh, int mw)
{
    mapHeight = mh;
    mapWidth = mw;
    makeRoom(rooms);
    rooms.assign(5, Rect(1,1,1,1));
    rooms.clear();
}

void Map::vDigDig(int start, int stop, int y)
{
int i;
    for (i = min(start, stop); i < max(start, stop); i++)
    {
        layout[i][y].blocking = false;
    }
}

void Map::hDigDig(int start, int stop, int x)
{
    int i;
    for (i = min(start, stop); i < max(start, stop); i++)
    {
        layout[x][i].blocking = false;
    }
}


void Map::carveRoom(Rect room)
{
    int x, y;
for (y = min(room.y1, room.y2); y < max(room.y1,room.y2) - 1; y++) {
    for (x = min(room.x1,room.x2); x < max(room.x1,room.x2) - 1; x++) {
            layout[x][y].blocking = false;
        }
    }
}

void Map::cleanUp()
{
    int x, y;
    for (y = 0; y < mapHeight; y++) {
        for (x = 0; x < mapWidth; x++) {
            //i've said that to say this....
            if (layout[x][y].blocking == true && layout[x+1][y].blocking == false && layout[x-1][y].blocking== false &&
                 layout[x][y + 1].blocking == false && layout[x][y-1].blocking == false)
                 { layout[x][y].blocking == false;std::cout<<"theres always one.";}

            if (layout[x][y].blocking == true && layout[x+1][y].blocking == false)
            {layout[x][y].borders = true;}
            if (layout[x][y].blocking == false && layout[x+1][y].blocking == true)
            {layout[x+1][y].borders = true;}
            if (layout[x][y].blocking == false && layout[x][y+1].blocking == true)
            {layout[x][y+1].borders = true;}
            if (layout[x][y].blocking == false && layout[x][y - 1].blocking == true)
            {layout[x][y - 1].borders = true;}
        }
    }
    for (x = 0; x < mapWidth; x++)
    { layout[x][5].borders = true; layout[x][mapHeight - 1].borders = true;}
    for (y = 0; y < mapHeight; y++)
    { layout[0][y].borders = true; layout[mapWidth - 1][y].borders = true;}
    for (y = 0; y < mapHeight; y++) {
        for (x = 0; x < mapWidth; x++) {
                if (layout[x][y].blocking == true && layout[x+1][y].blocking == false && layout[x-1][y].blocking== false &&
                 layout[x][y + 1].blocking == false && layout[x][y-1].blocking == false)
                 { layout[x][y].blocking == false;std::cout<<"theres always one.";}
        }
    }
}


void Map::makeRoom(std::vector<Rect> rooms)
{
  int i, p, numRooms = 0;
  int oldX, oldY;
  int sX, sY;
  for (i = 0; i < 20; i++) {
    std::cout<<"oi!"<<i<<std::endl;
    int w = getrand(7, 9);
    int h = getrand(5, 9);
    int x = getrand(1, mapWidth - w - 1);
    int y = getrand(1, mapHeight - h - 1);
    if (x > mapWidth - 10 || x + w > mapWidth - 5)
    {
        std::cout<<"x to big : "<<i;
    } else if (y > mapHeight - 10 || y + h > mapWidth - 5)
    {
        std::cout<<"y too big: "<<i;
        
    } else if (x < 5 || x + w < 5) {
        
        std::cout<<"x too small: "<<i;
    } else if (y < 5 || y + h < 5) {
        std::cout<<"y too small: "<<i;
        
    } 
    Rect room(x, y, w, h);
    if (i == 0) { 
        rooms.push_back(room);
        numRooms++; 
    } else {
        for (p = 0; p < numRooms; p++) {
            if (room.collides(rooms[p]))
            {
                break;
            } else {
                rooms.push_back(room);
                carveRoom(room);
                sY = room.cy;
                sX = room.cx;
                oldX = rooms[i - 1].cx;
                oldY = rooms[i - 1].cy;
         
                if (getrand(1,2) == 1) {
                    vDigDig(oldX, sX, oldY);
                    hDigDig(oldY, sY, sX);
                } else {
                    hDigDig(oldY, sY, oldX);
                    vDigDig(oldY, sX, sY);
                }
                numRooms++;
            }
          }
      }
    }
 cleanUp();
}