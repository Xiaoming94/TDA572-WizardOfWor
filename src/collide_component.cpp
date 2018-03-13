#include "collide_component.h"

void CollideComponent::Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Collidable> * coll_objects)
{
	Component::Create(system, go, game_objects);
	this->coll_objects = coll_objects;
}


void CollideComponent::Update(float dt)
{
	for (auto i = 0; i < coll_objects->pool.size(); i++)
	{
		Collidable * to = coll_objects->pool[i];
		if (to->enabled)
		{
			if ((to->horizontalPosition > go->horizontalPosition - 10) &&
				(to->horizontalPosition < go->horizontalPosition + 10) &&
				(to->verticalPosition   > go->verticalPosition - 10) &&
				(to->verticalPosition   < go->verticalPosition + 10))
			{
				go->Receive(to -> collide());
				to->Receive(HIT);
			}
		}
	}
}

