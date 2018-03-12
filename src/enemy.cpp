#include "enemy.h"
#include <random>
#include <sstream>


void EnemyBehaviourComponent::Create(AvancezLib* system,
                                    MovingGameObject * mgo,
                                    std::set<GameObject*> * game_objects,
                                    Map * game_map)
{
    Component::Create(system,mgo,game_objects);
    int sx = 0;
    int sy = 0;
    Wall * tile = game_map -> tileAt(sx,sy);
    mgo -> horizontalPosition = tile -> horizontalPosition;
    mgo -> verticalPosition = tile -> verticalPosition;
    std::stringstream print;
    print << "x : " << mgo -> horizontalPosition << " y : " << mgo -> verticalPosition;

    SDL_Log(print.str().c_str());
}


void Enemy::Create(EnemyType et)
{
    MovingGameObject::Create();
    this -> et = et;
}

void Enemy::SetEnemyType(EnemyType et)
{
    this ->  et = et;
}

EnemyType Enemy::GetEnemyType()
{
    return this -> et;
}

void Enemy::Receive(Message m)
{
    if(enabled && m == HIT)
        SDL_Log("I am HIT");
        enabled = false;
}

void EnemyRenderComponent::Create (
            AvancezLib* system,
            GameObject * go,
            std::set<GameObject*> * game_objects,
            EnemyType et
        )
{
    SDL_Log("EnemyRenderComponent::Create");
    const char * sprite_name;
    switch(et)
    {
        case EnemyType::BURWOR :
            sprite_name = BURWOR_SPRITE;
            break;
        case EnemyType::GARWOR :
            sprite_name = GARWOR_SPRITE;
            break;
        case EnemyType::THORWOR :
            sprite_name = THORWOR_SPRITE;
            break;
        case EnemyType::WORLUK :
            sprite_name = WORLUK_SPRITE;
            break;
        case EnemyType::WIZARD :
            sprite_name = WIZARD_SPRITE;
            break;
        default :
            sprite_name = BURWOR_SPRITE;
    }
    SDL_Log(sprite_name);
    RenderComponent::Create(system, go, game_objects, sprite_name);
}

void EnemyRenderComponent::Update(float dt)
{
    RenderComponent::Update(dt);
}
