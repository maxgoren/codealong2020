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

bFirst::bFirst(dungeon* map)
{
   this->map = map;
   Point N({0,-1,'^'});
   Point S({0,1,'v'});
   Point E({1,0,'>'});
   Point W({-1,0,'<'});
   Point NW({-1,1});
   Point NE({1,1});
   Point SW({-1,-1});
   Point SE({1,-1});
   cdir[0]=E; cdir[1]=N; cdir[2]=W; cdir[3]=S;
   cdir[4]=NW; cdir[5]=SE; cdir[6]=SW; cdir[7]=NE;
}

bool bFirst::inBounds(Point p)
{
     return 0 <= p.x && p.x < map->mapW && 0 <= p.y && p.y < map->mapH;
}

void bFirst::addNeighbors(Point current, Point target)
{
 bool beenchecked = false;
 for (auto dir : cdir)
 {
   Point next;
   next = new Point({current.x + dir.x, current.y + dir.y, dir.s});
   if ((inBounds(next) && map->layout[next.x][next.y].blocks == false) || (map->layout[next.x][next.y].blocks && map->layout[next.x][next.y].populated))
   {
     for (auto all : camefrom)
     {
       if (all.first.x == next.x && all.first.y == next.y)
         beenchecked = true;
     }
       if (beenchecked == false) 
       {
         que.push(next);
         camefrom[next] = current;
       }
       beenchecked = false;
    }
  }
}

bool bFirst::bFS(Point origin, Point target, int range)
{
   Point start;
   Point current;
   int level = 0;
   start = origin;
   camefrom.clear();
   while (!que.empty()) que.pop();
   que.push(start);
   camefrom[start] = start;
   que.push(Point({666,666}));
   while (!que.empty())
   {
      current = que.pop();
      if (current.x == 666) {
       level++;
       que.push(Point({666,666}));
      }
      if (current.x == target.x && current.y == target.y)
      { return true;  }
      if (level > range)
        return false;
      addNeighbors(current, target);
   }
return false;
}

MaxCode::Queue<Point> bFirst::getPath(Point start, Point target)
{
   std::vector<Point> path;
   MaxCode::Queue<Point> retPath;
   bFS(start, target, 3000);
   Point current = target;
   while (current.x != target.x && current.y != target.y) {
         path.push_back(current);
   }
   std::reverse(path.begin(),path.end());
   for (auto p: path)
   {
      retPath.push(p);
   }
   return retPath;
}
