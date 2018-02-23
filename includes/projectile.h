#ifndef PROJECTILE_H
#define PROJECTILE_H
enum Direction
{
    UP;
    DOWN;
    LEFT;
    RIGHT;
};

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
    virtual Direction getDirection();
};
#endif // PROJECTILE_H
