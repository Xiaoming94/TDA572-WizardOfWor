#ifndef ASTAR_AICOMPONENT_H
#define ASTAR_AICOMPONENT_H

#include "aicomponent.h"
#include <vector>


//The Basic AI Component that implements A*

class Node
{
    public:
        double cost;
        double x;
        double y;
        // Vector of Directions which represents the directions taken
        std::vector<Direction> path;
        Node(double x, double y, double cost)
        {
            this -> x = x;
            this -> y = y;
            this -> cost = cost;
        }
};

class TargetChecker
{
    public:
        std::vector<Collidable> targets;
        TargetChecker(ObjectPool<Collidable> * targets)
        {
            for(Collidable * t : targets -> pool)
            {
                this -> targets.push_back(*t);
            }
        };
        // Checks if a certain coordinate is close enough to the target
        bool CheckCloseEnough(double x, double y);
};

class AstarAIComponent : public AIComponent
{
    public:
        virtual void Update(float dt);
        Direction getNextWalkingDirection(float change);
};

#endif // ASTAR_AICOMPONENT_H
