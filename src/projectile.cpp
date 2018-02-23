#include "projectile.h"
#include "constants.h"


void ProjectileBehaviourComponent::Update(float dt, Direction dir){
    switch (dir)
    {
    case Direction::UP:
        go->verticalPosition -= ROCKET_SPEED * dt;
        break;
    case Direction::DOWN:
        go->verticalPosition += ROCKET_SPEED * dt;
        break;
    case Direction::LEFT:
        go->horizontalPosition -= ROCKET_SPEED * dt;
        break;
    case Direction::RIGHT:
        go->horizontalPosition += ROCKET_SPEED * dt;
        break;
    default: break;
    }
    //Check out of bounds
    if(go->horizontalPosition > 480 ||
       go->horizontalPosition < 0 ||
       go->verticalPosition > 640 ||
       go->verticalPosition < 0)
        go->enabled = false;
}

void Projectile::Init(double xPo, double yPo)
{
    SDL_Log("Projectile::Init");
    GameObject::Init();
    horizontalPosition = xPo;
    verticalPosition = yPo;
}

void Projectile::Receive(Message m)
{
    if(enabled && m == HIT)
    {
        enabled = false;
        SDL_Log("Projectile::HIT");
    }
}

