#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "wall.h"

const int mapW = 5;
const int mapH = 2;

class Map
{
    public:
        Map();
        ~Map();
        void create(std :: string map_model,AvancezLib* system);
        void draw();
        Wall * tileAt(double x, double y);
    protected:
        std::vector<std::vector<Wall*>> the_map;
    private:
};

Map * create_standard_map(AvancezLib* system);
#endif // MAP_H
