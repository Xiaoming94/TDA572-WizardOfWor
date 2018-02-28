#ifndef MOVINGCOMPONENT_H
#define MOVINGCOMPONENT_H

#include "component.h"
#include "moving_game_object.h"

class MovingComponent : public Component
{
    public:
        MovingGameObject * mgo;
        void Create(AvancezLib* system,
                    MovingGameObject * mgo,
                    std::set<GameObject*> * game_objects);
};

#endif // MOVINGCOMPONENT_H
