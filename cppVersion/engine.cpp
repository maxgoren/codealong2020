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


engine::engine() : gameStatus(GAMESTART)
{
 map = new dungeon(120, 35);
 map->chooseDungeon(10, 13);
 //map->makeRoom(10,13);
 knowledgeBase();
 ai = new dijk(map);
 fillMap();
 deathmatch = new Battle(map->mapW, map->mapH);
 me = new ent(map->spos.x, map->spos.y, 666,'@', "aT the Goblin King");
 gui = new Gui(1,1,map->mapW + 2,map->mapH - 2,160,45);
}

void engine::newLevel(int numRooms, int numMonsters)
{
     walkable.clear();
    goblins.clear();
    while (!guiding_light.empty()) guiding_light.pop();
    booty.clear(); 
    delete map;
    delete ai;
    map = new dungeon(120,36);
    map->makeRoom(10,13);
    knowledgeBase();
    ai = new dijk(map);
    fillMap();
}

void engine::update()
{ 
  std::string retmsg;
  std::string msg;
  bool stairCheck;
  int k;
  gameStatus = IDLE;
  if (terminal_has_input())
  {
   k=terminal_read();
   if (gameStatus == IDLE)
   {
   switch (k)
   {
        case TK_Q: terminal_close(); exit(0); break;
        case TK_UP:     stairCheck = me->move(map,0,-1, goblins); break;
        case TK_DOWN:   stairCheck = me->move(map,0,1, goblins); break;
        case TK_LEFT:   stairCheck = me->move(map,-1,0, goblins); break;
        case TK_RIGHT:  stairCheck = me->move(map,1,0, goblins); break;
        case TK_P:      std::tie(retmsg, booty) = me->checkItem(booty);
                        msg = me->name + " found " + retmsg + "!";
                        gui->gamelog.push_back(msg); break;
        case TK_TAB:    break;
        default: break;
   
   }
    if (stairCheck == true)
    {
        newLevel(10, 13);
    }
    gameStatus = NEW_TURN;
   } 
  
  }
  if (gameStatus == NEW_TURN)
  {
      dispatch();
      gameStatus = IDLE;
  }

  map->render(map);
  me->render();
  gui->drawGui(me, map, goblins);
  for (auto b : booty)
  {
      b->render();
  }
  for (auto q : goblins)
  {
      q->render();
  }
  terminal_refresh();
}

//Goblins and Items
void engine::fillMap()
{
    int q = 0;
    std::queue<Point>* trail;
    Point* mission;
    ent* goblin;
    item* fillerup;
    //create goblins and items, place them on map
    while (q < 7)
    {   
        auto r = walkable.at(getrand(1,walkable.size() - 1));
        auto p = walkable.at(getrand(1,walkable.size() - 1));
        fillerup = new item(*p);
        booty.push_back(fillerup);
        if (q % 2 == 0) {
        goblin = new ent(r->x, r->y, getrand(1,500), 'g', "goblin");
        goblins.push_back(goblin); }
        if (getrand(1,50)>25)
        {
        r = walkable.at(getrand(1,walkable.size() - 1));
        goblin = new ent(r->x, r->y, getrand(1,500), 'o', "orc");  
        goblins.push_back(goblin);
        p = walkable.at(getrand(1,walkable.size() - 1));
        fillerup = new item(*p);
        booty.push_back(fillerup);    
        } else {
            p = walkable.at(getrand(1,walkable.size() - 1));
            if (getrand(1,10)>5) {
                r = walkable.at(getrand(1,walkable.size() - 1));
                goblin = new ent(r->x, r->y, getrand(1,500), 'M', "maven");
                goblins.push_back(goblin); 
                }
                p = walkable.at(getrand(1,walkable.size() - 1));
        fillerup = new item(*p);
        booty.push_back(fillerup);
        }
        q++;
    }
   std::vector<item*>::iterator ranitm;
   //assign either an item, or a a random place to dispatch goblin to.
   for (auto dude : goblins)
   {
       
        ranitm = booty.begin();
        std::advance(ranitm,getrand(1, booty.size()-1));
        mission = new Point((*ranitm)->pos);
        trail = new std::queue<Point>(ai->getDijkPath(dude->pos, *mission));
        guiding_light.push(std::make_tuple(dude,*mission,*trail));
    }
    //iterate through the rooms, finding the farthest reachable spot from @, place stairs Down,
    //stairs up go right next to spos
    float farthest = 2;
    float distance;
    Point from(map->spos.x,map->spos.y);
    Point downStairs;
    for (auto places : map->rooms)
    {
        distance = ai->eucdist(from, places->cent);
        if (distance > farthest)
        {
            farthest = distance;
            map->stairsDown = places->cent;
        }
    }    
}

void engine::knowledgeBase()
{
    int x,y;
    for (x = 0; x < map->mapW; x++)
    {
        for (y = 0; y < map->mapH; y++)
        {
            if (map->layout[x][y].blocks == false)
            {
                map->layout[x][y].x = x;
                map->layout[x][y].y = y;
                walkable.push_back(&map->layout[x][y]);
            }
        }
    }
}

void engine::dispatch()
{
    std::queue<std::tuple<ent*,Point,std::queue<Point>>> temp;
    MaxCode::Queue<Point> battlePath;
    std::queue<Point> path;
    std::string msg;
    Point dest;
    Point step;
    ent* dude;
    bFirst bf(map);
    while(!guiding_light.empty())   //deathMatch.thunderDome(me, dude);
    {
        std::tie(dude,dest,path) = guiding_light.front(); //unpack the goblin, destination, path.
        guiding_light.pop(); //popped so next round we pick the next goblin
 
        if (dude->alive)
        {   
            switch (dude->pathfinding)
            {
              case true:
                if (dude->checkForEnemy(map, me->pos) == true)
                {
                    msg = "A " + dude->name + " notices " + me->name +"!!";
                    gui->gamelog.push_back(msg);
                    std::cout<<msg<<"\n";
                    dude->pathfinding = false;
                    dude->dumbstep(map, me, deathmatch);
                    dude->freestep++;
                    temp.push(std::make_tuple(dude, dest, path));
                }     
                step = path.front();
                path.pop();
                if (step != dest)
                {
                 dude->autostep(map, step, me);
                   for (auto itm : booty)   //check if you come across any random items
                   {
                     if (itm->pos.x == dude->pos.x && itm->pos.y == dude->pos.y)
                     {
                         msg = dude->name + " almost tripped over a " + itm->name + " in the dark..";
                         gui->gamelog.push_back(msg);
                         gui->banner();
                         dude->inventory.push_back(itm);
                         std::swap(itm, booty.back());
                         booty.pop_back();
                     }
                   }
                   temp.push(std::make_tuple(dude, dest, path));
                } else {
                  //at destination, pick up item if its still there.
                  dude->autostep(map,step, me);            
                  temp.push(goblinFoundItem(dude));
                }
                break;
              case false:
                if (dude->freestep + 1 < 5)
                {
                    dude->dumbstep(map, me, deathmatch);
                    dude->freestep++;
                } else {
                    std::random_shuffle(booty.begin(),booty.end());
                    auto next = booty.front();
                    dest = next->pos;
                    while (!path.empty()) path.pop();
                    path = ai->getDijkPath(dude->pos, dest);
                    temp.push(std::make_tuple(dude, dest, path));
                }
                break;
            }
        }
    } 
    std::swap(temp,guiding_light);
}

std::tuple<ent*,Point,std::queue<Point> > engine::goblinFoundItem(ent* goblin)
{
    std::queue<Point> path;
    std::tuple<ent*,Point,std::queue<Point>> errand;
    std::string msg;
    Point dest;
    std::tie(msg, booty) = goblin->checkItem(booty);  
    if (booty.size() > 2)
    {
            std::random_shuffle(booty.begin(), booty.end());
            auto next = booty.front();
            dest = next->pos;   
    } else {     
            std::random_shuffle(walkable.begin(), walkable.end());
            auto spot = walkable.front();
            dest = spot;
    }
        path = ai->getDijkPath(goblin->pos,dest);   
        errand = std::make_tuple(goblin,dest,path);
    return errand;
}

