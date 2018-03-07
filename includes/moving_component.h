#ifndef MOVINGCOMPONENT_H
#define MOVINGCOMPONENT_H

#include "component.h"
#include "moving_game_object.h"
#include "map.h"

struct PossibleDirections
{
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
};

class MovingComponent : public Component
{

    public:
        MovingGameObject * mgo;
        void Create(AvancezLib* system,
                    MovingGameObject * mgo,
                    std::set<GameObject*> * game_objects,
                    Map * game_map);
        void CheckWallBound(Wall * current_tile);
        PossibleDirections GetPossibleDirs(Wall * current_tile);
        Map * game_map;
};

#endif // MOVINGCOMPONENT_H
