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

dijk::dijk(dungeon* map)
{
   this->map = map;
   Point N({0,-1,'^'});
   Point S({0,1,'v'});
   Point E({1,0,'>'});
   Point W({-1,0,'<'});
   cdir[0]=E; cdir[1]=N; cdir[2]=W; cdir[3]=S;
}

bool dijk::inBounds(Point p)
{
     return 0 <= p.x && p.x < map->mapW && 0 <= p.y && p.y < map->mapH;
}

int dijk::effort_now(Point A) const
{
   return A.costm;
}

int dijk::eucdist(Point A, Point B)
{
  int dx = A.x - B.x;
  int dy = A.y - B.y;
  return sqrtf(pow(dx, 2) + pow(dy,2));
}

int dijk::heuristic(Point A, Point B)
{
   return std::abs(A.x - B.x) + std::abs(A.y - B.y);
}


void dijk::addDijkNeighbors(Point current, Point target)
{
int thiscost = 0;
Point best;
for (auto dir : cdir)
{
   Point next(current.x + dir.x, current.y + dir.y, dir.s);
   next.costm = map->layout[next.x][next.y].costm;
   if (inBounds(next) && map->layout[next.x][next.y].blocks == false)
   {
     for (auto all : effort)
     {
        thiscost = effort_now(next) + effort[current]; 
        if (effort.find(next) == effort.end() || thiscost < next.costm+ effort[current])
        {
            effort[next] = thiscost;
            camefrom[next] = current;
            pque.emplace(next, thiscost + heuristic(next, target));
         }  
        }
      }
    }
}

void dijk::dijkSearch(Point origin, Point target)
{
   Point start;
   Point current;
   start = origin;
   pque.emplace(start, start.costm);
   camefrom[start] = start;
   effort[start] = 0;
   while (!pque.empty())
   {
      current = pque.top().value;
      pque.pop();
      if (current == target)
          break;
      addDijkNeighbors(current, target);
   }
}

std::queue<Point> dijk::getDijkPath(Point start, Point target)
{
   this->reset();
   std::vector<Point> path;
   std::queue<Point> retPath;
   if (inBounds(target))
   {
     dijkSearch(start, target);
     Point current = target;
     while (current != start) {
      path.push_back(current);
      current = camefrom[current];
     }
     path.push_back(start);
     std::reverse(path.begin(),path.end());
   } else {
      path.push_back(start);
   }
   for (auto step : path)
   {
      retPath.push(step);
   }
   retPath.pop();
   return retPath;
}

void dijk::reset()
{
 while (!pque.empty())
 {
  pque.pop();
 }
 camefrom.clear();
 effort.clear();
}
