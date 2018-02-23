#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "direction.h"
#include "component.h"
#include "game_object.h"

class ProjectileBehaviourComponent : public Component
{
public:
    void Update(float dt,Direction dir);
};


// rockets are shot by the player towards the aliens
class Projectile : public GameObject
{
public:
    virtual void Init(double xPo,double yPo);
    virtual void Receive(Message m);
};
#endif // PROJECTILE_H
