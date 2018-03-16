#ifndef ASTAR_AICOMPONENT_H
#define ASTAR_AICOMPONENT_H

#include "aicomponent.h"

//The Basic AI Component that implements A*

class Node
{
    public:
        double cost;
        GameObject go;
        Node(GameObject go, double cost)
        {
            this -> cost = cost;
            this -> go = go;
        }
};

class targetCheck
{

};

class AstarAIComponent : public AIComponent
{
    public:
        virtual void Update(float dt);
        Direction getNextWalkingDirection(float change);
};

#endif // ASTAR_AICOMPONENT_H
