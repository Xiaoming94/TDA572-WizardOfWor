#include "moving_component.h"
#include <iostream>

// Helper function
bool isDirectionValid(MovingGameObject * go, float move, Direction dir, Map * m)
{
    if (dir == Direction::NONE)
        return true;
    double newHPos = go -> horizontalPosition;
    double newVPos = go -> verticalPosition;
    switch(dir)
    {
        case Direction::LEFT :
            newHPos = newHPos - move;
            break;
        case Direction::UP :
            newVPos = newVPos - move;
            break;
        case Direction::RIGHT :
            newHPos = newHPos + move;
            break;
        case Direction::DOWN :
            newVPos = newVPos + move;
            break;
        default :
            break;
    }
    return m -> isPositionValid(int(newHPos), int(newVPos));
}

void MovingComponent::Create(AvancezLib* system,
                        MovingGameObject * mgo,
                        std::set<GameObject*> * game_objects,
                        Map * game_map)
{
    Component::Create(system, mgo, game_objects);
    this -> mgo = mgo;
    this -> game_map = game_map;
}

PossibleDirections MovingComponent::GetPossibleDirs(float move)
{
    PossibleDirections dir;
    dir.left = isDirectionValid(this -> mgo, move, Direction::LEFT, game_map);
    dir.up = isDirectionValid(this -> mgo, move, Direction::UP, game_map);
    dir.right = isDirectionValid(this -> mgo, move , Direction::RIGHT, game_map);
    dir.down = isDirectionValid(this -> mgo, move, Direction::DOWN, game_map);
    return dir;
}
