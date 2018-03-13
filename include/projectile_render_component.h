#ifndef PROJECTILERENDERCOMPONENT_H
#define PROJECTILERENDERCOMPONENT_H

#include "component.h"
#include "moving_game_object.h"

class ProjectileRenderComponent : public RenderComponent
{
    public:
        virtual void Create(AvancezLib* system, MovingGameObject * go, std::set<GameObject*> * game_objects, const char * sprite_name);
        virtual void Update(float dt);

    private:
        MovingGameObject * mgo;
};

#endif // PROJECTILERENDERCOMPONENT_H
