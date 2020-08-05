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

class engine {
   public:
    enum GameStatus {
       GAMESTART,
       IDLE,
       NEW_TURN,
       VICTORY,
       GAMEOVER
    } gameStatus;
    Gui* gui;
    dungeon* map;
    Battle* deathmatch;
    ent* me;
    dijk* ai;
    std::vector<Point*> walkable;
    std::vector<ent*> goblins;
    std::vector<item*> booty;
    std::vector<Point> path;
    std::queue<std::tuple<ent*,Point, std::queue<Point>> > guiding_light;
    void dispatch();
    void knowledgeBase();
    void fillMap();
    void newLevel(int, int);
    void update();
    bool assigned(Point dest);
    std::tuple<ent*,Point,std::queue<Point> >  goblinFoundItem(ent*);
    engine();
};