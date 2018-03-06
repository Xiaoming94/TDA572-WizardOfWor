#include "wall.h"

void Wall::Create(double x, double y, WallType wt)
{
    GameObject::Create();
    this -> horizontalPosition = x;
    this -> verticalPosition = y;
    this -> wt = wt;
}

void Wall::Update()
{
    GameObject::Update(0.1f);
}

void Wall::Destroy()
{
    GameObject::Destroy();
}

void WallRenderComponent::Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, WallType wt)
{
    switch (wt)
    {
        case WallType::BOTH_H :
            SDL_Log("Wall Creating::BOTH_H");
            RenderComponent::Create(system, go, game_objects, WALL_BH_SPRITE);
            break;
        case WallType::BOTH_V :
            SDL_Log("Wall Creating::BOTH_V");
            RenderComponent::Create(system, go, game_objects, WALL_BV_SPRITE);
            break;
        case WallType::CORNER_BL :
            SDL_Log("Wall Creating::CBL");
            RenderComponent::Create(system, go, game_objects, WALL_CBL_SPRITE);
            break;
        case WallType::CORNER_BR :
            SDL_Log("Wall Creating::CBR");
            RenderComponent::Create(system, go, game_objects, WALL_CBR_SPRITE);
            break;
        case WallType::CORNER_TL :
            SDL_Log("Wall Creating::CTL");
            RenderComponent::Create(system, go, game_objects, WALL_CTL_SPRITE);
            break;
        case WallType::CORNER_TR :
            SDL_Log("Wall Creating::CTR");
            RenderComponent::Create(system, go, game_objects, WALL_CTR_SPRITE);
            break;
        case WallType::DOWN :
            RenderComponent::Create(system, go, game_objects, WALL_D_SPRITE);
            break;
        case WallType::LEFT :
            RenderComponent::Create(system, go, game_objects, WALL_L_SPRITE);
            break;
        case WallType::UP :
            RenderComponent::Create(system, go, game_objects, WALL_U_SPRITE);
            break;
        case WallType::RIGHT :
            RenderComponent::Create(system, go, game_objects, WALL_R_SPRITE);
            break;
        default:
            SDL_Log("Invalid WallType");
            break;

    }

}

void  WallRenderComponent::Destroy()
{
    RenderComponent::Destroy();
}
