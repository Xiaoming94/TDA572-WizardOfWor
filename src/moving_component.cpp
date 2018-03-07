#include "moving_component.h"

void MovingComponent::Create(AvancezLib* system,
                        MovingGameObject * mgo,
                        std::set<GameObject*> * game_objects,
                        Map * game_map)
{
    Component::Create(system, mgo, game_objects);
    this -> mgo = mgo;
    this -> game_map = game_map;
}

void MovingComponent::CheckWallBound(Wall * current_tile)
{
    switch(current_tile -> getWallType())
    {
        case WallType::BOTH_H :
            if(go -> horizontalPosition > current_tile -> horizontalPosition
                || go -> horizontalPosition < current_tile -> horizontalPosition)
                go -> horizontalPosition = current_tile -> horizontalPosition;
            break;
        case WallType::BOTH_V :
            if(go -> verticalPosition > current_tile -> verticalPosition
                || go -> verticalPosition < current_tile -> verticalPosition)
                go -> verticalPosition = current_tile -> verticalPosition;
            break;
        case WallType::CORNER_BL :
            if(go->horizontalPosition < current_tile-> horizontalPosition)
                go->horizontalPosition = current_tile-> horizontalPosition;
            if(go->verticalPosition > current_tile-> verticalPosition)
                go->verticalPosition = current_tile-> verticalPosition;
            break;
        case WallType::CORNER_BR :
            if(go->horizontalPosition > current_tile-> horizontalPosition)
                go->horizontalPosition = current_tile-> horizontalPosition;
            if(go->verticalPosition > current_tile-> verticalPosition)
                go->verticalPosition = current_tile-> verticalPosition;
            break;
        case WallType::CORNER_TL :
            if(go->horizontalPosition < current_tile-> horizontalPosition)
                go->horizontalPosition = current_tile-> horizontalPosition;
            if(go->verticalPosition < current_tile-> verticalPosition)
                go->verticalPosition = current_tile-> verticalPosition;
            break;
        case WallType::CORNER_TR :
            if(go->horizontalPosition > current_tile-> horizontalPosition)
                go->horizontalPosition = current_tile-> horizontalPosition;
            if(go->verticalPosition < current_tile-> verticalPosition)
                go->verticalPosition = current_tile-> verticalPosition;
            break;
        case WallType::DOWN :
            if(go->verticalPosition > current_tile->verticalPosition)
                go->verticalPosition = current_tile->verticalPosition;
            break;
        case WallType::LEFT :
            if(go->horizontalPosition < current_tile->horizontalPosition)
                go->horizontalPosition = current_tile->horizontalPosition;
            break;
        case WallType::UP :
            if(go->verticalPosition < current_tile->verticalPosition)
                go->verticalPosition = current_tile->verticalPosition;
            break;
        case WallType::RIGHT :
            if(go->horizontalPosition > current_tile->horizontalPosition)
                go->horizontalPosition = current_tile->horizontalPosition;
            break;
        default:
            break;

        }
}
