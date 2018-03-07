#include "direction.h"
#include "moving_component.h"
#include "moving_game_object.h"
#include "map.h"

class PlayerBehaviourComponent : public MovingComponent
{
	float time_fire_pressed;	// time from the last time the fire button was pressed
	ObjectPool<Projectile> * projectiles_pool;

public:
	virtual ~PlayerBehaviourComponent() {}

	virtual void Create(AvancezLib* system, MovingGameObject * go, std::set<GameObject*> * game_objects, Map * game_map ,ObjectPool<Projectile> * projectiles_pool)
	{
		MovingComponent::Create(system, go, game_objects, game_map);
		this->projectiles_pool = projectiles_pool;
		go -> horizontalPosition = game_map -> tileAt(mapW-1,mapH-1) -> horizontalPosition;
		go -> verticalPosition = game_map -> tileAt(mapW-1,mapH-1) -> verticalPosition;
	}

	virtual void Init()
	{
		time_fire_pressed = -10000.f;
	}

	virtual void Update(float dt)
	{
		AvancezLib::KeyStatus keys;
		system->getKeyStatus(keys);
		if (keys.right)
			Move(dt * PLAYER_SPEED, Direction::RIGHT);
		else if (keys.left)
			Move(-dt * PLAYER_SPEED, Direction::LEFT);
        else if (keys.up)
            Move(-dt * PLAYER_SPEED, Direction::UP);
        else if (keys.down)
            Move(dt * PLAYER_SPEED, Direction::DOWN);
		if (keys.fire)
		{
			if (CanFire())
			{
				// fetches a Projectile from the pool and use it in game_objects
				Projectile * projectile = projectiles_pool->FirstAvailable();
				if (projectile != NULL)	// Projectile is NULL is the object pool can not provide an object
				{
					projectile->Init(mgo->horizontalPosition,mgo->verticalPosition,mgo -> getDirection());
					game_objects->insert(projectile);
				}
			}
		}
	}


	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move, Direction dir)
	{
	    this -> mgo -> setDirection(dir);
	    if(dir == Direction::UP || dir == Direction::DOWN)
            go->verticalPosition += move;
        else
            go->horizontalPosition += move;
    // Check maze boundaries;
        Wall * current_tile = game_map -> tileAt(go -> horizontalPosition,go -> verticalPosition);
        MovingComponent::CheckWallBound(current_tile);
	}

	// return true if enough time has passed from the previous Projectile
	bool CanFire()
	{
		// shoot just if enough time passed by
		if ((system->getElapsedTime() - time_fire_pressed) < (FIRE_TIME_INTERVAL / game_speed))
			return false;

		time_fire_pressed = system->getElapsedTime();

		SDL_Log("fire!");
		return true;
	}
};


// the main player
class Player : public MovingGameObject
{
public:

	int lives;	// it's game over when goes below zero

	virtual ~Player()	{		SDL_Log("Player::~Player");	}

	virtual void Init()
	{
		SDL_Log("Player::Init");
		GameObject::Init();
		lives = NUM_LIVES;
	}

	virtual void Receive(Message m)
	{
		if (m == HIT)
		{
			SDL_Log("Player::Hit!");
			RemoveLife();

			if (lives < 0)
				Send(GAME_OVER);
		}
	}

	void RemoveLife()
	{
		lives--;
		SDL_Log("remaining lives %d", lives);
	}
};
