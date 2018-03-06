#include "map.h"
#include "constants.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>

Map::Map(){}

Map::~Map()
{
     for(std::vector<Wall*> map_row : the_map){
        for(Wall * wall_tile : map_row){
            wall_tile -> Destroy();
            delete wall_tile;
        }
    }
}
void Map::create(std::string map_model,AvancezLib* system)
{
    SDL_Log("Map::Create");
    std::stringstream mapss(map_model);
    std::string mapRow;
    int x = 0;
    while(std::getline(mapss, mapRow, '\n'))
    {
        std::stringstream mapRowSS(mapRow);
        std::string tile;
        int y = 0;
        std::vector<Wall*> map_row;
        while(std::getline(mapRowSS,tile,','))
        {
            // Translates the grid coordinate to In game Pixel coordinates
            double realx = double(3 * SPRITE_SIDE + x * SPRITE_SIDE);
            double realy = double(3 * SPRITE_SIDE + y * SPRITE_SIDE);
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
            wall_tile -> Create(realy, realx ,wt);
            wall_tile -> AddComponent(wrc);
            map_row.push_back(wall_tile);
            y++;
        }
        std::reverse(map_row.begin(),map_row.end());
        the_map.push_back(map_row);
        x++;
    }
    std::reverse(the_map.begin(),the_map.end());
    SDL_Log(std::to_string(the_map.size()).c_str());

}

void Map::draw()
{
    for (int i = 0; i < the_map.size(); i++)
    {
        for(int j = 0; j < the_map.at(i).size(); j++)
        {
            the_map.at(i).at(j) -> Update();
        }
    }
}

Wall * Map::tileAt(double x, double y)
{
    int mapX = int(std::round(x * X_MAPSCALE));
    int mapY = int(std::round(y * Y_MAPSCALE));
    if(mapX < 0 || mapX > mapW || mapY < 0 || mapY > mapH)//Check boundaries
    {
        return NULL;
    }
    else
        return the_map.at(mapY).at(mapX);
}

Map * create_standard_map(AvancezLib* system)
{
    std::string standardMap = "ctl,bv,bv,bv,bv,ctr\ncbl,bv,bv,bv,bv,cbr";
    Map * the_map = new Map();
    the_map -> create(standardMap, system);
    return the_map;
}

