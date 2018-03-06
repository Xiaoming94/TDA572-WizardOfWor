#include "map.h"
#include "constants.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>


Map::Map(){}

void Map::Create(std::string map_model,AvancezLib* system)
{
    SDL_Log("Map::Create");
    std::stringstream mapss(map_model);
    std::string mapRow;
    int y = startingY;
    while(std::getline(mapss, mapRow, '\n'))
    {
        std::stringstream mapRowSS(mapRow);
        std::string tile;
        int x = startingX;
        std::vector<Wall*> map_row;
        while(std::getline(mapRowSS,tile,','))
        {
            // Translates the grid coordinate to In game Pixel coordinates
            std::cout << "x : " << x << " y : " << y << "\n";
            Wall * wall_tile;
            WallRenderComponent * wrc = new WallRenderComponent();
            WallType wt;
            if(!tile.compare("ctl"))
                wt = WallType::CORNER_TL;
            else if(!tile.compare("ctr"))
                wt = WallType::CORNER_TR;
            else if(!tile.compare("bv"))
                wt = WallType::BOTH_V;
            else if(!tile.compare("cbl"))
                wt = WallType::CORNER_BL;
            else if(!tile.compare("cbr"))
                wt = WallType::CORNER_BR;

            wall_tile = new Wall();
            wrc -> Create(system, wall_tile, NULL, wt);
            wall_tile -> Create(x, y ,wt);
            wall_tile -> AddComponent(wrc);
            wall_tile -> Init();
            map_row.push_back(wall_tile);
            x+=32;
        }
        std::reverse(map_row.begin(),map_row.end());
        the_map.push_back(map_row);
        y+=32;
    }
    std::reverse(the_map.begin(),the_map.end());
    SDL_Log(std::to_string(the_map.size()).c_str());

}

std::vector<std::vector<Wall *>> Map::get_map()
{
    return this -> the_map;
}

Wall Map::tileAt(int x, int y)
{
    return *the_map.at(x).at(y);
}

Map * create_standard_map(AvancezLib* system)
{
    std::string standardMap = "ctl,bv,bv,bv,bv,ctr\ncbl,bv,bv,bv,bv,cbr";
    Map * the_map = new Map();
    the_map -> Create(standardMap, system);
    return the_map;
}

