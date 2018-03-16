#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "moving_component.h"
#include "collidable.h"
#include "heuristics.h"
#include "avancezlib.h"

class AIComponent : public MovingComponent
{
    public:
        AIComponent(){}
        virtual ~AIComponent(){}
        void Create(
           AvancezLib* system,
           MovingGameObject * mgo,
           std::set<GameObject*> * game_objects,
           Map * game_map,
           Heuristics h
        );
        virtual void Update(float dt) = 0;
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
        void SetTargets(ObjectPool < Collidable> * targets);
        virtual Direction getNextWalkingDirection(float change)=0;


    protected:
        ObjectPool <Collidable> * targets;
        Heuristics h;
        float time_fire_pressed;
    private:
};

#endif // AICOMPONENT_H
