#include "moving_component.h"
#include <iostream>

// Helper function
bool isDirectionValid(MovingGameObject * go, float dt, float speed, Direction dir, Map * m)
{
    if (dir == Direction::NONE)
        return true;
    double newHPos = go -> horizontalPosition;
    double newVPos = go -> verticalPosition;
    switch(dir)
    {
        case Direction::LEFT :
            newHPos = newHPos - dt * speed;
            break;
        case Direction::UP :
            newVPos = newVPos - dt * speed;
            break;
        case Direction::RIGHT :
            newHPos = newHPos + dt * speed;
            break;
        case Direction::DOWN :
            newVPos = newVPos + dt * speed;
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

PossibleDirections MovingComponent::GetPossibleDirs(float dt, float speed)
{
    PossibleDirections dir;
    dir.left = isDirectionValid(this -> mgo, dt, speed, Direction::LEFT, game_map);
    dir.up = isDirectionValid(this -> mgo, dt, speed, Direction::UP, game_map);
    dir.right = isDirectionValid(this -> mgo, dt, speed, Direction::RIGHT, game_map);
    dir.down = isDirectionValid(this -> mgo, dt, speed, Direction::DOWN, game_map);
    return dir;
}
