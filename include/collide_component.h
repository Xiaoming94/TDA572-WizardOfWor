#ifndef COLLIDECOMPONENT_H
#define COLLIDECOMPONENT_H

#include "component.h"
#include "collidable.h"


class CollideComponent : public Component
{
	ObjectPool<Collidable> * coll_objects; // collision will be tested with these objects

public:
	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Collidable> * coll_objects);
	virtual void Update(float dt);
};

#endif // COLLIDECOMPONENT_H
