/*
Copyright (c) 2020 Max Goren 
maxgoren@icloud.com
http://www.maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
class ent {
public:
  std::array<Point, 8> cdir;
  Point pos;
  char ch[2];
  std::string name;
  int id;
  double maxhealth;
  double health;
  double strength;
  double defence;
  int freestep;
  bool alive;
  bool pathfinding;
  std::vector<item*> inventory;
  static bool inBounds(Point*);
  static bool canWalk(dungeon*, int, int);
  bool isStairs(dungeon*);
  std::tuple<std::string, std::vector<item*>> checkItem(std::vector<item*> booty);
  bool move(dungeon*, int x, int y, std::vector<ent*> goblins);
  void autostep(dungeon* map, Point target, ent* player);
  void dumbstep(dungeon* map, ent* player, Battle* deathmatch);
  bool checkForEnemy(dungeon* map, Point target);
  void die();
  void render();
  ent(int x, int y, int id, char ch, std::string name);
  ~ent();
};



