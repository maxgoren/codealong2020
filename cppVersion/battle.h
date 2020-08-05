
struct battleStats {
  float health;
  float power;
  float defence;
};


class Battle {
private:
Point arena[120][40];
int mapW;
int mapH;
std::vector<std::string> battlelog;
public:
void thunderDome(ent* player, ent* goblin);
void buildArena();
bool attack(ent*, ent*);
void battleGui(ent* player, ent* goblin);
void moveGoblin(ent* goblin, ent* player);
void playerMove(ent* player, int dx, int dy);
void render(ent* player, ent* goblin);
Battle(int mapW, int mapH);
};