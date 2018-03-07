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
            if(go -> horizontalPosition >= current_tile -> horizontalPosition
                || go -> horizontalPosition <= current_tile -> horizontalPosition)
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

PossibleDirections MovingComponent::GetPossibleDirs(Wall * current_tile)
{
    PossibleDirections dirs;
    switch(current_tile -> getWallType())
    {
        case WallType::BOTH_H :
            if(go -> horizontalPosition >= current_tile -> horizontalPosition
                || go -> horizontalPosition <= current_tile -> horizontalPosition)
                dirs.left = false;
                dirs.right = false;
            break;
        case WallType::BOTH_V :
            if(go -> verticalPosition >= current_tile -> verticalPosition
                || go -> verticalPosition <= current_tile -> verticalPosition)
                dirs.up = false;
                dirs.down = false;
            break;
        case WallType::CORNER_BL :
            if(go->horizontalPosition <= current_tile-> horizontalPosition)
                dirs.left = false;
            if(go->verticalPosition >= current_tile-> verticalPosition)
                dirs.down = false;
            break;
        case WallType::CORNER_BR :
            if(go->horizontalPosition >= current_tile-> horizontalPosition)
                dirs.right = false;
            if(go->verticalPosition >= current_tile-> verticalPosition)
                dirs.down = false;
            break;
        case WallType::CORNER_TL :
            if(go->horizontalPosition <= current_tile-> horizontalPosition)
                dirs.left = false;
            if(go->verticalPosition <= current_tile-> verticalPosition)
                dirs.up = false;
            break;
        case WallType::CORNER_TR :
            if(go->horizontalPosition >= current_tile-> horizontalPosition)
                dirs.right = false;
            if(go->verticalPosition <= current_tile-> verticalPosition)
                dirs.up = false;
            break;
        case WallType::DOWN :
            if(go->verticalPosition >= current_tile->verticalPosition)
                dirs.down = false;
            break;
        case WallType::LEFT :
            if(go->horizontalPosition <= current_tile->horizontalPosition)
                dirs.left = false;
            break;
        case WallType::UP :
            if(go->verticalPosition <= current_tile->verticalPosition)
                dirs.up = false;
            break;
        case WallType::RIGHT :
            if(go->horizontalPosition >= current_tile->horizontalPosition)
                dirs.right = false;
            break;
        default:
            break;

        }
        return dirs;
}
