#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "moving_component.h"
#include "collidable.h"
#include "heuristics.h"
#include "avancezlib.h"

class AIComponent : public MovingComponent
{
    public:
        void Create(
           AvancezLib* system,
           MovingGameObject * mgo,
           std::set<GameObject*> * game_objects,
           Map * game_map,
           Heuristics h
        );
        void Update(float dt);
        bool canshot()
        {
            extern float game_speed;
            // shoot just if enough time passed by
            if ((system->getElapsedTime() - time_fire_pressed) < (FIRE_TIME_INTERVAL / game_speed))
                return false;

            time_fire_pressed = system->getElapsedTime();

            SDL_Log("fire!");
            return true;
        }
        virtual Direction getNextWalkingDirection(float dt);


    protected:
        ObjectPool <Collidable> * targets;
        Heuristics h;
        float time_fire_pressed;
    private:
};

#endif // AICOMPONENT_H
