#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "wall.h"
#include "constants.h"

const int mapW = 8;
const int mapH = 6;
const int startX = 3 * SPRITE_SIDE;
const int startY = 3 * SPRITE_SIDE;

class Map
{
    public:
        Map();
        ~Map();
        void create(std :: string map_model,AvancezLib* system);
        void draw();
        Wall * tileAt(double x, double y);
        Wall * tileAt(int x, int y);
    protected:
        std::vector<std::vector<Wall*>> the_map;
    private:
};

Map * create_standard_map(AvancezLib* system);
#endif // MAP_H
