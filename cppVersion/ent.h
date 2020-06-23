
class Entity {
    public:
    int px,py;
    char ch;
    void move(int x, int y);
    Entity(int x, int y, char ch);
};

Entity::Entity(int x, int y, char ch)
{
    px = x;
    py = y;
    ch = ch;
}

void Entity::move(int x, int y)
{
      terminal_layer(1);
      terminal_print(px, py, " ");
      px += x;
      py += y;
      terminal_color("purple");
      terminal_print(px, py, "@"); 
}
