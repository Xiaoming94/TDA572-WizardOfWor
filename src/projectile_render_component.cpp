#include "projectile_render_component.h"

void ProjectileRenderComponent::Create(AvancezLib* system,
                                       MovingGameObject * mgo,
                                       std::set<GameObject*> * game_objects,
                                       const char * sprite_name)
{
    RenderComponent::Create(system, mgo, game_objects, sprite_name);
    this -> mgo = mgo;
}

void ProjectileRenderComponent::Update(float dt)
{
    return;
}
