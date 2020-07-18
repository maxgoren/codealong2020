  
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
enum direction {
 North,
 South,
 East,
 West
};

struct Point {
 int x;
 int y;
 bool operator==(const Point& other) const {
  return x == other.x && y == other.y;
 }
 bool operator!=(const Point& other) const {
     return x != other.x && y != other.y;
 }
 int operator=(int other) {
     return x + other && y + other;
 }
 int operator+(int other) {
   x += other; 
   y += other;
   return x&&y;
 }
};


struct Tiles {
 Point pos;
 int isinRoom = 0;
 int value = 1000;
 bool beenover = false;
 bool populated = false;
 bool blocks = true;
 bool border = false;
 ~Tiles() {}
};

class Rect {
public:
 Point uL;
 Point lR;
 Point cent;
 int width;
 int height;
 int idNum;
 int numItems = 0;
 int numEnts = 0;
 bool collision(Rect other);
 Rect(int x, int y, int w, int h);
 Rect();
 ~Rect() {}
};

struct attributes {
    std::string name;
    std::string heals;
    std::string power;
};

class Map {
public:
 int spx, spy;
 int width;
 int height;
 Tiles layout[140][40];
 bool fov = false;
 std::vector<Rect> scrSect;
 std::vector<Rect> rooms;
 std::vector<ent*> badGuys;
 std::vector<Items*> itemList;

 double isInFov(int, int, int, int);
 void roomVal();
 void setValue(Point* pPos);
 void digRect(Rect room);
 void genRect(int numRoom, int maxSize);
 void connectRooms(std::vector<Rect>);
 void connectRooms2(std::vector<Rect>);
 void connectR2R(Rect st, Rect fi);
 void outline();
 void spawnMonsters(int);
 void placeItems(int);
 void placePortal();
 Map (int w, int h);
 ~Map() {}
};
