Battle::Battle(int mapW, int mapH)
{
    this->mapW = mapW;
    this->mapH = mapH;
    buildArena(); 
}

void Battle::buildArena()
{
    int centx = mapW/2; 
    int centy = mapH/2;
    int x, y;
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            arena[x][y].blocks = true;
            arena[x][y].border = true;
            arena[x][y].s = '#';
        }
    }
    for (x = centx - 20; x < centx + 20; x++)
    {
        for (y = centy - 10; y < centy + 10; y++)
        {
            arena[x][y].blocks = false;
            arena[x][y].border = false;
            arena[x][y].s = '.';
        }
    }
}

void Battle::render(ent* player, ent* goblin)
{
  int centx = mapW/2; 
  int centy = mapH/2;
  int x, y;
  terminal_clear();
  terminal_layer(1);
  for (x = centx - 30; x < centx + 30; x++)
  {
      for (y = centy - 15; y < centy + 15; y++)
      {
          terminal_printf(x, y, "%c", arena[x][y].s);
          if (arena[x][y].blocks == false)
          {
            terminal_layer(2);
            terminal_color("#8b4513");
            terminal_put(x, y, 57643);
          }
          if (arena[x][y].border == true)
          {
            terminal_layer(2);
            terminal_color("#c2c2c2");
            terminal_put(x,y,57643);
          }
      }
  }
  terminal_layer(2);
  player->render();
  goblin->render();
  battleGui(player, goblin);
  terminal_refresh();
}

void Battle::moveGoblin(ent* goblin, ent* player)
{
   Point playerPos = player->pos;
   Point goblinPos = goblin->pos;
   int dx = playerPos.x - goblinPos.x;
   int dy = playerPos.y - goblinPos.y;
   int stepdx = (dx > 0 ? 1:-1);
   int stepdy = (dy > 0 ? 1:-1);
   float distance=sqrtf(dx*dx+dy*dy);
       dx = (int)(round(dx/distance));
       dy = (int)(round(dy/distance));
    if (distance >= 2) {
       if (arena[goblinPos.x+dx][goblinPos.y+dy].blocks == false) {
           arena[goblinPos.x][goblinPos.y].blocks = false;
           goblin->pos.x += dx;
           goblin->pos.y += dy;
           arena[goblinPos.x][goblinPos.y].blocks = true;   
       }
    } else {
        attack(goblin, player);
    }
}

void Battle::playerMove(ent* player, int dx, int dy)
{
   if (arena[player->pos.x+dx][player->pos.y+dy].blocks == false) 
   {
        arena[player->pos.x][player->pos.y].blocks = false;
        player->pos.x += dx;
        player->pos.y += dy;
        arena[player->pos.x][player->pos.y].blocks = true;
   }
}

void Battle::thunderDome(ent* player, ent* goblin)
{  
    bool turn = true;
    int k;
    int centx = mapW/2;
    int centy = mapH/2;
    std::string msg;
    player->pos.x = centx-3;
    player->pos.y = centy-3;
    goblin->pos.x = centx+3;
    goblin->pos.y = centy+3;
    msg = player->name + " and " + goblin->name + " are in a fight to the death!";
    battlelog.push_back(msg);
    while (player->health > 0 && goblin->health > 0)
    {
        if (terminal_has_input())
        {
            if (turn == true)
            {
              k = terminal_read();
              switch (k)
              {
                    case TK_UP:     playerMove(player, 0,-1); break;
                    case TK_DOWN:   playerMove(player, 0,1); break;
                    case TK_LEFT:   playerMove(player, -1,0); break;
                    case TK_RIGHT:  playerMove(player, 1,0); break;
                    case TK_A:      attack(player, goblin); break;
                    case TK_I:      goblin->health = -5;
                                    battlelog.push_back(msg = player->name + " uses the unforgivable curse!!!"); break;
                    default: break;
              }
            }
            turn = false;
        }
        if (turn == false)
        {
            moveGoblin(goblin, player);
            turn = true;
        }
        render(player, goblin);
    }
    while ((k = terminal_read()) != TK_Q) { }
}

bool Battle::attack(ent* giver, ent* taker)
{
   std::string msg;
   double dmg = giver->strength - taker->defence;
   Point playerPos = giver->pos;
   Point goblinPos = taker->pos;
   int dx = playerPos.x - goblinPos.x;
   int dy = playerPos.y - goblinPos.y;
   float distance=sqrtf(dx*dx+dy*dy);
   if (distance <= 2)
   {
     msg = giver->name + " Attacks " + taker->name + " for " + std::to_string(dmg) + " damage!";
     battlelog.push_back(msg);
     dmg -= getrandfloat(0.3,0.7);
    if (dmg > 0)
    {
        taker->health -= dmg;
    }
    if (taker->health <= 0)
    {
        taker->die();
        return false;
    }
   }
    return true;
}

void Battle::battleGui(ent* player, ent* goblin)
{
 int x, y;
 int scrH = this->mapH+10;
 int scrW = this->mapW+20;  
 std::map<std::string, std::string> box;
 box["uL"] =  "[U+250F]";
 box["lL"] = "[U+2517]";
 box["uR"] = "[U+2513]";
 box["lR"] = "[U+2518]";
 box["side"] = "[U+2503]";
 box["top"] = "[U+2501]";

 terminal_layer(2);
 terminal_color("red");
 terminal_print(2,scrH-11, box["uL"].c_str());       
 terminal_print(2,scrH-10, box["side"].c_str());
 terminal_print(2,scrH-9, box["side"].c_str());
 terminal_print(2,scrH-8, box["side"].c_str());
 terminal_print(2,scrH-7, box["side"].c_str());
 terminal_print(2,scrH-6, box["side"].c_str());
 terminal_print(2,scrH-5, box["side"].c_str());
 terminal_print(2,scrH-4, box["side"].c_str());
 terminal_print(2,scrH-3, box["side"].c_str());
 terminal_print(2,scrH-2,  box["lL"].c_str());
 terminal_print(scrW-40,scrH-11, box["uR"].c_str());
 terminal_print(scrW-40,scrH-10, box["side"].c_str());
 terminal_print(scrW-40,scrH-9, box["side"].c_str());
 terminal_print(scrW-40,scrH-8, box["side"].c_str());
 terminal_print(scrW-40,scrH-7, box["side"].c_str());
 terminal_print(scrW-40,scrH-6, box["side"].c_str());
 terminal_print(scrW-40,scrH-5, box["side"].c_str());
 terminal_print(scrW-40,scrH-4, box["side"].c_str());
 terminal_print(scrW-40,scrH-3, box["side"].c_str());
 terminal_print(scrW-40,scrH-2, box["lR"].c_str());
 terminal_layer(3);

 for (x = 3; x < scrW - 40; x++)
 {
  terminal_print(x,scrH-11, box["top"].c_str()); 
  terminal_print(x,scrH-2, box["top"].c_str());
 }
std::string messagebuff;
int m = scrH-10; int l = 0;
int sat = 255;
if (battlelog.size() >= 1){
 for (auto i = battlelog.rbegin();  i < battlelog.rend(); i++)
 {
   messagebuff = *i;
   if (m + l < scrH-2)
   {
        terminal_layer(4);
        terminal_color(color_from_argb(sat,255,255,255));
        terminal_clear_area(3,m+l,40,1);
        terminal_printf(4, m + l, "%s", messagebuff.c_str());
        sat-=25;
   }
   l++;
 }
}
    terminal_color("white");
    terminal_print(4, scrH-11, "Battle log");
/************************************************/
 // player health bar

  terminal_bkcolor("black");
  double health_unit = player->maxhealth / 13;
  double health_amt = (player->health) / health_unit;
  int health_bar = 20 + health_amt;
  terminal_layer(3);
  terminal_color("white");
  terminal_print(10, 7, "Player Health");
  terminal_printf(15, 9, "%f%", player->health);
  terminal_layer(0);
  terminal_bkcolor("red");
  for (x = 10; x < 23; x++)
  {
    terminal_print(x, 9, " ");
  }
  terminal_bkcolor("green");
  for (x = 10; x < health_bar - 2; x++)
  {
    terminal_print(x, 9, " ");
  }
  terminal_bkcolor("black");
  /***************************************/
  
  double gobhealth_unit = goblin->maxhealth / 13;
  double gobhealth_amt = (goblin->health) / gobhealth_unit;
  int gobhealth_bar = 93 + gobhealth_amt;
  terminal_layer(3);
  terminal_color("white");
  terminal_print(93, 7, "Goblin Health");
  terminal_printf(93, 9, "%f%", goblin->health);
  terminal_layer(0);
  terminal_bkcolor("red");
  for (x = 93; x < 105; x++)
  {
    terminal_print(x, 9, " ");
  }
  terminal_bkcolor("green");
  for (x = 933; x < gobhealth_bar - 2; x++)
  {
    terminal_print(x, 9, " ");
  }
   terminal_bkcolor("black");
}