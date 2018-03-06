#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "wall.h"
#include "constants.h"

const int mapW = 5;
const int mapH = 2;
const int startingX = 3 * SPRITE_SIDE;
const int startingY = 3 * SPRITE_SIDE;

class Map
{
    public:
        Map();
        void Create(std :: string map_model,AvancezLib* system);
        std::vector<std::vector<Wall*>> get_map();
        Wall tileAt(int x, int y);
    protected:
        std::vector<std::vector<Wall*>> the_map;
    private:
};

Map * create_standard_map(AvancezLib* system);
#endif // MAP_H
