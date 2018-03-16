#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "map.h"
#include "object_pool.h"
#include <queue>
#include <vector>
#include "moving_component.h"
#include "collidable.h"

/**
 * A vector where the indices corresponds to the values of the following directions:
 * 0: UP
 * 1: LEFT
 * 2: DOWN
 * 3: RIGHT
 */
typedef std::vector<double> HeuristicVec;

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
        virtual HeuristicVec movement (
            PossibleDirections dirs,           // Possible direction in a given tick.
            ObjectPool <Collidable> * targets, // ObjectPool of targets.
            double x, double y                 // Coordinate of the AI Using these heuristics in double space for precision
        ){ HeuristicVec hvec; return hvec; }

        // Heuristics for Shooting a certain target
        virtual bool shoot(Collidable * target){ return false; }

};

#endif // HEURISTICS_H
