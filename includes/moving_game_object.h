#ifndef MOVING_GAME_OBJECT_H
#define MOVING_GAME_OBJECT_H

#include "game_object.h"
#include "direction.h"

class MovingGameObject : public GameObject
{
    public:
        Direction getDirection();
        void setDirection(Direction dir);
    protected:
        Direction dir;
    private:
};

#endif // MOVING_GAME_OBJECT_H
