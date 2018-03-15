#ifndef ASTAR_AICOMPONENT_H
#define ASTAR_AICOMPONENT_H

#include "aicomponent.h"

//The Basic AI Component that implements A*

class AstarAIComponent : public AIComponent
{
    public:
        virtual void Update(float dt);
        Direction getNextWalkingDirection(float dt);
};

#endif // ASTAR_AICOMPONENT_H
