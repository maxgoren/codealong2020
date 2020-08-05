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


struct Point {
  int x;
  int y;
  char s;
  int level;
  int costm;
  bool blocks;
  bool populated;
  bool border;
  color_t color;
  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Point& other) const {
    return x != other.x || y != other.y;
  }
  bool operator < (const Point& other) const {
      return std::tie(x,y) < std::tie(other.x,other.y);
  }

  bool operator > (const Point& other) const {
      return std::tie(x,y) > std::tie(other.x, other.y);
  }

  Point operator=(Point* other) {
    x = other->x;
    y = other->y;
    s = other->s;
    costm = other->costm;
    color = other->color;
    blocks = other->blocks;
    populated = other->populated;
    return *other;
  }
 
  Point operator=(Point other) {
      x = other.x;
      y = other.y;
      s = other.s;
      costm = other.costm;
      color = other.color;
      blocks = other.blocks;
      populated = other.populated;
      return other;
  }

  Point operator+(Point other) {
    x += other.x;
    y += other.y;
    return Point({x,y,'F'});
  }
  Point(int x, int y, char s, int cost) : x(x), y(y), s(s), costm(cost) { }
  Point(int x, int y, int s) : x(x), y(y), s(s) { }
  Point(int x, int y) : x(x), y(y) { }
  Point() = default;
 
};
 
struct Colors {
    // 0x80 <- half transparent
    // 0xFF <- solid
    color_t stone = 0xFFcecece;
    color_t wood =  0xFFC19A6B;
    color_t green = 0xFF00FF00;
    color_t red =   0xFFFF0000;
    color_t yellow = 0xFFFFFF00;
    color_t blue = 0XFF0000FF;
    //DIRECTIONS
    color_t west = yellow;
    color_t east = blue;
    color_t south = green; 
    color_t north = red;

};

class Room {
public:
 Point uL;
 Point lR;
 Point cent;
 int x, y, w, h;
 int id;
 bool collision(Room other); 
 Room* childA = NULL;
 Room* childB = NULL;
 bool splitRoom();
 Room* makeRoom();
 Room* getRoom();
 Room(int x, int y, int w, int h, int ID);
 Room() = default;
};

class dungeon {
public:
int mapW;
int mapH;
Point spos;
Point stairsDown;
Point layout[130][45];
std::vector<Room*> rooms;
std::vector<Room*> cells;
std::queue<Room*> nodes;
std::array<Room, 7> scrSect;
bool passCheck(Room*);
void render(dungeon*);
void dig(Room*);
void outLine();
void chooseDungeon(int, int);
void makeRoom(int, int);
void placeStairs(Point);
void startBSP();
void conRoomStyle1(std::vector<Room*>);
void conRoomStyle2(std::vector<Room*>);
void crNB1(std::vector<Room*>);
void crNB2(std::vector<Room*>);
dungeon(int w, int h);
~dungeon();
};
