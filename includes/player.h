#include "direction.h"

class PlayerBehaviourComponent : public Component
{
	float time_fire_pressed;	// time from the last time the fire button was pressed
	ObjectPool<Projectile> * projectiles_pool;

public:
    Direction dir;
	virtual ~PlayerBehaviourComponent() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Projectile> * projectiles_pool)
	{
		Component::Create(system, go, game_objects);
		this->projectiles_pool = projectiles_pool;
	}

	virtual void Init()
	{
		go->horizontalPosition = 320;
		go->verticalPosition = 480 - 32;

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
		else if (keys.fire)
		{
			if (CanFire())
			{
				// fetches a Projectile from the pool and use it in game_objects
				Projectile * projectile = projectiles_pool->FirstAvailable();
				if (projectile != NULL)	// Projectile is NULL is the object pool can not provide an object
				{
					projectile->Init(go->horizontalPosition,go->verticalPosition,this -> dir);
					game_objects->insert(projectile);
				}
			}
		}
	}


	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move, Direction dir)
	{
	    this -> dir = dir;
	    if(dir == Direction::UP || dir == Direction::DOWN)
            go->verticalPosition += move;
        else
            go->horizontalPosition += move;

		if (go->horizontalPosition > (640 - 32))
			go->horizontalPosition = 640 - 32;

		if (go->horizontalPosition < 0)
			go->horizontalPosition = 0;

        if (go->verticalPosition > (480 - 32))
            go->verticalPosition = 480 - 32;

        if (go->verticalPosition < 0)
            go->verticalPosition = 0;
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
class Player : public GameObject
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
