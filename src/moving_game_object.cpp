#include "moving_game_object.h"

Direction MovingGameObject::getDirection()
{
    return this->dir;
}

void MovingGameObject::setDirection(Direction dir)
{
    this -> dir = dir;
}
void MovingGameObject::setGameMap(Map* game_map)
{
    this -> game_map = game_map;
}
