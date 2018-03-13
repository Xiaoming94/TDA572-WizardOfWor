#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "moving_game_object.h"

class Collidable : public MovingGameObject
{
    public:
        virtual Message collide() {return Message::HIT; };
};

#endif // COLLIDABLE_H
