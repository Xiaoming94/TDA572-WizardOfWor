#include "component.h"
#include "game_object.h"
#include "avancezlib.h"

void Component::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects)
{
	this->go = go;
	this->system = system;
	this->game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, const char * sprite_name)
{
	Component::Create(system, go, game_objects);

	sprite = system->createSprite(sprite_name);
	if(sprite)
    {
        SDL_Log("Sprite::INIT SUCCESS");
    }
    else
        SDL_Log("SPRITE::INIT FAILED");
}

void RenderComponent::Update(float dt)
{
	if (!go->enabled)
		return;

	if (sprite){
        sprite->draw(int(go->horizontalPosition), int(go->verticalPosition));
	}

}

void RenderComponent::Destroy()
{
	if (sprite != NULL)
		sprite->destroy();
	sprite = NULL;
}


