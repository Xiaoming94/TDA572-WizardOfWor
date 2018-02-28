#include "moving_component.h"

void MovingComponent::Create(AvancezLib* system,
                        MovingGameObject * mgo,
                        std::set<GameObject*> * game_objects)
{
    Component::Create(system, mgo, game_objects);
    this -> mgo = mgo;
}
