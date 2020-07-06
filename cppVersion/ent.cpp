
ent::ent(int x, int y, std::string name, char ch, color_t col)
{
 this->pos.x = x;
 this->pos.y = y;
 this->sym[0] = ch;
 this->sym[1] = '\0';
 this->col = col;
 this->name = name;
}

void ent::move(Map map, int x, int y)
{
 if (map.layout[pos.x + x][pos.y + y].blocks == false)
 {
   this->pos.x += x;
   this->pos.y += y;
 }
}
void ent::render()
{
 terminal_layer(2);
 terminal_color("magenta");
 terminal_print(1 + pos.x, 6 + pos.y, sym);
}

void ent::kick(Map map, std::vector<std::string>* gamelog)
{
 Point enemy;
 std::string msg;
 int x=this->pos.x;
 int y=this->pos.y;
 switch (this->dir) {
 case North:
   if (map.layout[x][y-1].populated == true)
   {
    enemy=map.layout[x][y-1].pos;
   }
   break;
 case South:
   if (map.layout[x][y+1].populated == true)
   {
    enemy=map.layout[x][y+1].pos;
   }
   break;
 case East:
  if (map.layout[x+1][y].populated == true)
  {
   enemy=map.layout[x+1][y].pos;
  }
  break;
 case West:
 if (map.layout[x-1][y].populated == true)
 {
  enemy=map.layout[x-1][y].pos;
 }
  break;
 default: break;
 }
 for (auto m : map.badGuys)
 {
  if (enemy == m.pos)
  {
   msg = "The " + m.name + "howls in rage at your attack.";
   gamelog->push_back(msg);
  }
 }
 //std::cout<<gamelog.at(0)<<"\n";
}
