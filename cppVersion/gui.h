class Gui {
public:
int scrW, scrH;
int mapW, mapH;
int mapX, mapY;
void drawGui(std::vector<std::string>*);
void banner(std::vector<std::string>*);
void fade(int x, int y,int start[3], int fin[3], char *message);
Gui(int, int, int, int, int, int);
};
