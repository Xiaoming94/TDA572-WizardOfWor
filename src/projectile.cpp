#include "projectile.h"
#include "constants.h"

bool IsWallCollision(MovingGameObject * mgo, Wall * tile)
{
    WallType wt = tile -> getWallType();
    switch(mgo -> getDirection())
    {
        case Direction::DOWN :

            if(wt == WallType::BOTH_V)
            {
                return true;
            }
            if(wt == WallType::CORNER_BL || wt == WallType::CORNER_BR ||
            wt == WallType::DOWN)
            {
                return mgo -> verticalPosition >= tile -> verticalPosition;
            }
            return false;
        case Direction::LEFT :
            if(wt == WallType::BOTH_H)
                return true;
            if(wt == WallType::CORNER_TL || wt == WallType::CORNER_BL ||
               wt == WallType::LEFT)
                return mgo -> horizontalPosition <= tile -> horizontalPosition;
            return false;
        case Direction::RIGHT :
            if(wt == WallType::BOTH_H)
                return true;
            if(wt == WallType::CORNER_TR || wt == WallType::CORNER_BR ||
               wt == WallType::RIGHT)
                return mgo -> horizontalPosition >= tile -> horizontalPosition;
            return false;
        case Direction::UP :
            if(wt == WallType::BOTH_V)
                return true;
            if(wt == WallType::CORNER_TL || wt == WallType::CORNER_TR ||
               wt == WallType::UP)
                return mgo -> verticalPosition <= tile -> verticalPosition;
            return false;
        default : return false;
    }
}

void ProjectileBehaviourComponent::Update(float dt){
    this -> Update(2*dt,mgo -> getDirection());
}


void ProjectileBehaviourComponent::Update(float dt, Direction dir){

    Wall * tile = this -> game_map -> tileAt(go->horizontalPosition,go->verticalPosition);

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

    if(IsWallCollision(this -> mgo, tile))
    {

        SDL_Log("Collision with Wall");
        mgo -> enabled = false;

    }

}

void Projectile::Init(double xPo, double yPo, Direction dir, MovingGameObject * owner)
{
    SDL_Log("Projectile::Init");
    GameObject::Init();
    horizontalPosition = xPo;
    verticalPosition = yPo;
    this -> dir = dir;
    this -> owner = owner;
}

void Projectile::Receive(Message m)
{
    owner -> Receive(m);
}


