#include <tuple>
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
  return x == other.x && y ==other.y;
 }
};

/*struct Pool {
  Point uL;
  char piece[4][4];
  piece[0][0]=' ';piece[0][1]='-';piece[0][2]='-';piece[0][3]=' ';  //  --
  piece[1][0]='|';piece[1][1]='~';piece[1][2]='~';piece[1][3]='|'; //  |~~|
  piece[2][0]='|';piece[2][1]='~';piece[2][2]='~';piece[2][3]='|';  // |~~|
  piece[3][0]=' ';piece[3][1]='-';piece[3][2]='-';piece[3][3]=' ';   // --
};*/

struct Tiles {
 Point pos;
 int isinRoom = 0;
 bool populated = false;
 bool blocks = true;
 bool border = false;
};

class Rect {
public:
 Point uL;
 Point lR;
 Point cent;
 int width;
 int height;
 int idNum;
 int numEnts = 0;
 bool collision(Rect other);
 Rect(int x, int y, int w, int h);
 Rect();
};

class Map {
public:
 int spx, spy;
 int width;
 int height;
 Tiles layout[80][40];
 std::vector<Rect> scrSect;
 std::vector<Rect> rooms;
 std::vector<ent> badGuys;
 void digRect(Rect room);
 void genRect(int numRoom, int maxSize);
 void connectRooms(std::vector<Rect>);
 void connectRooms2(std::vector<Rect>);
 void outline();
 void spawnMonsters(int);
 Map (int w, int h);
};
