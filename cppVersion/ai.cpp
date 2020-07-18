  
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
ai::ai()
{

}
/*
bool ai::canAttack(Map* map, Point* playerPos)
{

}*/
bool ai::canMove(Map* map, int pX, int pY) {
 if (map->layout[pX][pY].blocks)
 {
     return false;
 } else {
     return true;
 }
}
void ai::moveMonsters(Map* map, Point* playerPos)
{
int dx,dy;
int dis;
float dist;
  for (auto M : map->badGuys)
  {
    dx = M->pos.x - playerPos->x;
    dy = M->pos.y - playerPos->y;
    dist = sqrtf(pow(dx,2)+pow(dy,2));
    dx = (int)round(dx/dist);
    dy = (int)round(dy/dist);
    if (canMove(map, M->pos.x + dx, M->pos.y + dy))
    {
      map->layout[M->pos.x][M->pos.y].populated = false;
      map->layout[M->pos.x][M->pos.y].blocks = false;
      M->pos.x += dx;
      M->pos.y += dy;
      map->layout[M->pos.x][M->pos.y].blocks = true;
      map->layout[M->pos.x][M->pos.y].populated = true;
    }
  } 
}
