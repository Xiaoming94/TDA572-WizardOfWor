#include "aicomponent.h"

void AIComponent::Create(
    AvancezLib * system,
    MovingGameObject * mgo,
    std::set< GameObject* > * game_objects,
    Map * game_map,
    Heuristics h
)
{
    MovingComponent::Create(system, mgo, game_objects, game_map);
    this -> h = h;
    h.create(game_map);
}

void AIComponent::SetTargets(ObjectPool < Collidable > * targets)
{
    this -> targets = targets;
}
