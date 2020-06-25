
#include <vector>

class Tile {
public:
    bool blocking;
    bool borders;
    Tile() : blocking(true), borders(false) {}
};

class Rect {
public:
    int x1, x2;
    int y1, y2;
    int w, h;
    int cx, cy;
    bool collides(Rect other);
    Rect(int x, int y, int w, int h);
};

class Map {
public:
    int mapHeight;
    int mapWidth;
    int maxRooms;
    Tile layout[80][40];
    std::vector<Rect> rooms;
    void makeRoom(std::vector<Rect> rooms);
    void carveRoom(Rect room);
    void vDigDig(int start, int stop, int y);
    void hDigDig(int star, int stop, int x);
    void cleanUp();
    Map(int mh, int mw);
};

