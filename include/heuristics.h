#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "map.h"
#include "object_pool.h"
#include <queue>
#include <map>
#include "moving_component.h"
#include "collidable.h"

typedef std::map<double,Direction> HeuristicsMap;
//More a wrapper object for performing heuristics
class Heuristics
{
    private:
        Map * game_map;

    public:
        Heuristics(){};
        ~Heuristics(){};
        void create(Map * game_map);

        // Heuristics for movement on evaluating each tile
        virtual HeuristicsMap movement (
            PossibleDirections dirs,           // Possible direction in a given tick.
            ObjectPool <Collidable> * targets, // ObjectPool of targets.
            double x, double y                 // Coordinate of the AI Using these heuristics in double space for precision
        ){ HeuristicsMap hm; return hm; }

        // Heuristics for Shooting a certain target
        virtual bool shoot(Collidable * target){ return false; }

};

#endif // HEURISTICS_H
