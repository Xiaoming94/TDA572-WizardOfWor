#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "map.h"
#include "object_pool.h"
#include <queue>
#include <map>
#include "moving_component.h"
#include "collidable.h"

typedef std::map<double,Direction> heuMap;
//More a wrapper object for performing heuristics
class Heuristics
{
    private:
        Map * game_map;

    public:
        Heuristics();
        virtual ~Heuristics();
        void create(Map * game_map);

        // Heuristics for movement on evaluating each tile
        virtual heuMap movement (
            PossibleDirections dirs,           // Possible direction in a given tick.
            ObjectPool <Collidable> * targets, // ObjectPool of targets.
            double x, double y                 // Coordinate of the AI Using these heuristics in double space for precision
        );

        // Heuristics for Shooting a certain target
        virtual bool shoot(Collidable * target){ return false; }

};

#endif // HEURISTICS_H
