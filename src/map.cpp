#include "map.h"
#include "constants.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iostream>

struct MapBlock
{
    int block[SPRITE_SIDE][SPRITE_SIDE];
}currblock;

void getMapBlock(WallType wt)
{
    for (int i = 0; i < SPRITE_SIDE; i++)
    {
      for (int j = 0; j < SPRITE_SIDE; j++)
      {
        switch(wt){
          case WallType::BOTH_H :
            if(j < 2 || j > (SPRITE_SIDE - 3))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::BOTH_V :
            if(i < 2 || i > (SPRITE_SIDE - 3))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::CORNER_BL :
            if((i < (SPRITE_SIDE - 2) && j < 2) || i >= (SPRITE_SIDE - 2))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::CORNER_BR :
            if((i < (SPRITE_SIDE - 2) && j > (SPRITE_SIDE - 3) || i >= (SPRITE_SIDE - 2)))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::CORNER_TL :
            if(i < 2 || i >= 2 && j < 2)
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::CORNER_TR :
            if(i < 2 || i >= 2 && j > (SPRITE_SIDE - 3))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;

          case WallType::DOWN :
            if(i > (SPRITE_SIDE - 3))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::LEFT :
            if(j < 2)
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::UP :
            if(i < 2)
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          case WallType::RIGHT :
            if(j > (SPRITE_SIDE - 3))
              currblock.block[i][j] = 1;
            else
              currblock.block[i][j] = 0;
            break;
          default:
            currblock.block[i][j] = 0;
        }
      }
    }
}

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
    int y = startY;
    while(std::getline(mapss, mapRow, '\n'))
    {
        std::stringstream mapRowSS(mapRow);
        std::string tile;
        int x = startX;
        std::vector<Wall*> map_row;
        while(std::getline(mapRowSS,tile,','))
        {
            // Translates the grid coordinate to In game Pixel coordinates
            Wall * wall_tile;
            WallRenderComponent * wrc = new WallRenderComponent();
            WallType wt = WallType::NONE;
            if(!tile.compare("ctl"))
                wt = WallType::CORNER_TL;
            else if(!tile.compare("ctr"))
                wt = WallType::CORNER_TR;
            else if(!tile.compare("cbl"))
                wt = WallType::CORNER_BL;
            else if(!tile.compare("cbr"))
                wt = WallType::CORNER_BR;
            else if(!tile.compare("u"))
                wt = WallType::UP;
            else if(!tile.compare("d"))
                wt = WallType::DOWN;
            else if(!tile.compare("l"))
                wt = WallType::LEFT;
            else if(!tile.compare("r"))
                wt = WallType::RIGHT;
            else if(!tile.compare("bv"))
                wt = WallType::BOTH_V;
            else if(!tile.compare("bh"))
                wt = WallType::BOTH_H;

            wall_tile = new Wall();
            wall_tile -> Create(x,y,wt);
            if(wt != WallType::NONE)
            {
                wrc -> Create(system, wall_tile, NULL, wt);
                wall_tile -> AddComponent(wrc);
            }
            getMapBlock(wt);
            for(int i = 0; i < SPRITE_SIDE; i++){
              for(int j = 0; j < SPRITE_SIDE; j++)
              {
                bpmg[y-startY+i][x-startX+j] = currblock.block[i][j] == 1 ? true : false;

              }
            }
            map_row.push_back(wall_tile);
            x+=SPRITE_SIDE;
        }
        the_map.push_back(map_row);
        y+=SPRITE_SIDE;
    }
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
    x = x - static_cast<double>(startX);
    y = y - static_cast<double>(startY);
    int mapX = static_cast<int>(std::round(x/SPRITE_SIDE));
    int mapY = static_cast<int>(std::round(y/SPRITE_SIDE));
    if(mapX < 0 || mapX > mapW || mapY < 0 || mapY > mapH)//Check boundaries
    {
        return NULL;
    }
    else
        return this -> tileAt(mapX,mapY);
}
Wall * Map::tileAt(int x, int y)
{
    return the_map.at(y).at(x);
}


/**
 * Checks weather or not a position is valid in this maze
 * Assuming each cell in this maze is 32x32 and that each wall is 2pixels in width
 * Than testing for overlap with a wall pixel or not
 */
bool Map::isPositionValid(int x, int y)
{
    //Calculating the coordinates of the 28 x 28 object
    int objcordX1 = x + 2;               // Left edge
    int objcordX2 = objcordX1 + 28; // Right edge
    int objcordY1 = y + 2;               // Up edge
    int objcordY2 = objcordY1 + 28; // Down edge
    for(int i = objcordY1; i < objcordY2; i++)
    {
        for(int j = objcordX1; j < objcordX2; j++)
        {
            if(bpmg[i - startY][j - startX])
            {
                return false;
            }
        }
    }
    return true;
}

Map * create_standard_map(AvancezLib* system)
{
    const char * mapString =
    "ctl,bv,bv,u,bv,bv,u,ctr\n"
    "bh,ctl,bv,n,u,ctr,bh,bh\n"
    "bh,bh,ctl,r,bh,bh,bh,bh\n"
    "l,r,cbl,bh,bh,bh,bh,bh\n"
    "bh,cbl,bv,d,d,n,cbr,bh\n"
    "cbl,bv,bv,bv,bv,d,bv,cbr";

    std::string standardMap(mapString);
    Map * the_map = new Map();
    the_map -> create(standardMap, system);
    return the_map;
}
