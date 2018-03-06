#include "wall.h"

void Wall::Create(double x, double y, WallType wt)
{
    GameObject::Create();
    this -> horizontalPosition = x;
    this -> verticalPosition = y;
    this -> wt = wt;
    enabled = true; // Walls are always enabled
}

void Wall::setRender(WallRenderComponent * wcr)
{
    this -> wcr = wcr;
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
            RenderComponent::Create(system, go, game_objects, WALL_BH_SPRITE);
            break;
        case WallType::BOTH_V :
            RenderComponent::Create(system, go, game_objects, WALL_BV_SPRITE);
            break;
        case WallType::CORNER_BL :
            RenderComponent::Create(system, go, game_objects, WALL_CBL_SPRITE);
            break;
        case WallType::CORNER_BR :
            RenderComponent::Create(system, go, game_objects, WALL_CBR_SPRITE);
            break;
        case WallType::CORNER_TL :
            RenderComponent::Create(system, go, game_objects, WALL_CTL_SPRITE);
            break;
        case WallType::CORNER_TR :
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
