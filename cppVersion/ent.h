class ent {
public:
 Point pos;
 char sym[2];
 color_t col;
 std::string name;
 direction dir;
 void render();
 void kick(Map, std::vector<std::string>*);
 void move(Map, int, int);
 ent(int x, int y, std::string name, char ch, color_t col);
};
