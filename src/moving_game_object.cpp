#include "moving_game_object.h"

Direction MovingGameObject::getDirection()
{
    return this->dir;
}

void MovingGameObject::setDirection(Direction dir)
{
    this -> dir = dir;
}
