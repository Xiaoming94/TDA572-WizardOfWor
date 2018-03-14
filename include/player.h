#include "direction.h"
#include "moving_component.h"
#include "collidable.h"
#include "map.h"

#define PLAYER1_SPRITE "assets/WorriorGold.bmp"
#define PLAYER2_SPRITE "assets/WorriorBlue.bmp"


/**
 * A direction decider function
 * handles the player moving direction if the player cannot move in the soughtforDirection
 * This function is purely for User Experience enhancement
 * Handles everycases of Direction shifting
 * Assuming the player cannot move in a certain direction
 */
Direction decide_direction(MovingGameObject * mgo, Wall * tile, Direction soughtDir)
{
    WallType wt = tile -> getWallType();
    double diffX = mgo -> horizontalPosition - tile -> horizontalPosition;
    double diffY = mgo -> verticalPosition - tile -> verticalPosition;
    switch(soughtDir)
    {
        case Direction::UP :
        {
            if(wt == WallType::CORNER_TL || wt == WallType::CORNER_TR ||
               wt == WallType::UP || wt == WallType::BOTH_V ||diffY == 0.0)
               return Direction::NONE;
            else
            {
                if(diffX > 0.0)
                    return Direction::LEFT;
                else
                    return Direction::RIGHT;
            }
            break;
        }

        case Direction::LEFT :
            if(wt == WallType::CORNER_TL || wt == WallType::CORNER_BL ||
               wt == WallType::LEFT || wt == WallType::BOTH_H ||diffX == 0.0)
                return Direction::NONE;
            else
            {
                if(diffY > 0.0)
                    return Direction::UP;
                else
                    return Direction::DOWN;
            }
            break;

        case Direction::RIGHT :
            if(wt == WallType::CORNER_TR || wt == WallType::CORNER_BR ||
               wt == WallType::RIGHT || wt == WallType::BOTH_H || diffX == 0.0)
                return Direction::NONE;
            else
            {
                if(diffY > 0.0)
                    return Direction::UP;
                else
                    return Direction::DOWN;
            }

        case Direction::DOWN :
            if(wt == WallType::CORNER_BL || wt == WallType::CORNER_BR ||
               wt == WallType::DOWN || wt == WallType::BOTH_V || diffY == 0.0)
               return Direction::NONE;
            else
            {
                if(diffX > 0.0)
                    return Direction::LEFT;
                else
                    return Direction::RIGHT;
            }
            break;
        default :
            return Direction::NONE;
    }


}

class PlayerBehaviourComponent : public MovingComponent
{
	float time_fire_pressed;	// time from the last time the fire button was pressed
	ObjectPool<Projectile> * projectiles_pool;

public:
	virtual ~PlayerBehaviourComponent() {}

	virtual void Create(AvancezLib* system, MovingGameObject * go, std::set<GameObject*> * game_objects, Map * game_map ,ObjectPool<Projectile> * projectiles_pool, bool isPlayer1)
	{
		MovingComponent::Create(system, go, game_objects, game_map);
		this->projectiles_pool = projectiles_pool;
		if (isPlayer1)
        {
            go -> horizontalPosition = game_map -> tileAt(mapW-1,mapH-1) -> horizontalPosition;
            go -> verticalPosition = game_map -> tileAt(mapW-1,mapH-1) -> verticalPosition;
		}
		else
		{
            go -> horizontalPosition = game_map -> tileAt(0,mapH-1) -> horizontalPosition;
            go -> verticalPosition = game_map -> tileAt(0,mapH-1) -> verticalPosition;
		}

		this -> isPlayer1 = isPlayer1;
	}

	virtual void Init()
	{
		time_fire_pressed = -10000.f;
	}

	virtual void Update(float dt)
	{
        float posChange = dt * PLAYER_SPEED;
		KeyStatus keys = system->getKeyStatus(isPlayer1);
		//Check maze boundaries;
		PossibleDirections dirs = GetPossibleDirs(posChange);
		Wall * current_tile = game_map -> tileAt(mgo -> horizontalPosition, mgo -> verticalPosition);
		// On Keypress, check if direction is available,
		// Rotate once counter clockwise if not
		if (keys.right)
		{
            if(dirs.right)
                Move(posChange, Direction::RIGHT);
            else
            {
                Direction newDir = decide_direction(mgo, current_tile, Direction::RIGHT);
                Move(posChange, newDir);
            }
		}

		else if (keys.left)
		{
            if(dirs.left)
                Move(posChange, Direction::LEFT);
            else
            {

                Direction newDir = decide_direction(mgo, current_tile, Direction::LEFT);
                Move(posChange, newDir);

            }
		}

        else if (keys.up)
		{
            if(dirs.up)
                Move(posChange, Direction::UP);
            else
            {

                Direction newDir = decide_direction(mgo, current_tile, Direction::UP);
                Move(posChange, newDir);

            }

		}
        else if (keys.down)
		{
            if (dirs.down)
                Move(posChange, Direction::DOWN);
            else
            {

                Direction newDir = decide_direction(mgo, current_tile, Direction::DOWN);
                Move(posChange, newDir);

            }

		}

		if (keys.fire)
		{
			if (CanFire())
			{
				// fetches a Projectile from the pool and use it in game_objects
				Projectile * projectile = projectiles_pool->FirstAvailable();
				if (projectile != NULL)	// Projectile is NULL is the object pool can not provide an object
				{
					projectile->Init(mgo->horizontalPosition,mgo->verticalPosition,mgo -> getDirection(),this -> mgo);
					game_objects->insert(projectile);
				}
			}
		}
	}
	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move, Direction dir)
	{
	    if(dir != Direction::NONE)
            this -> mgo -> setDirection(dir);
	    switch(dir)
	    {
            case Direction::LEFT :
                mgo -> horizontalPosition -= move;
                break;

            case Direction::RIGHT :
                mgo -> horizontalPosition += move;
                break;

            case Direction::UP :
                mgo -> verticalPosition -= move;
                break;

            case Direction::DOWN :
                mgo -> verticalPosition += move;
                break;

            default:
                break;
	    }
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
private :
    bool isPlayer1;
};

class PlayerRenderComponent : public RenderComponent
{
    public:
        void Create(
            AvancezLib * system,
            GameObject * go,
            std::set<GameObject*>* game_objects,
            bool isPlayer1
        )
        {
            if(isPlayer1)
                RenderComponent::Create(system, go, game_objects, PLAYER1_SPRITE);
            else
                RenderComponent::Create(system, go, game_objects, PLAYER2_SPRITE);
        }

};

// the main player
class Player : public Collidable
{
public:

    int score = 0;
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
		if (m == HIT_BURWOR)
            score += 100;

	}

	void RemoveLife()
	{
		lives--;
		SDL_Log("remaining lives %d", lives);
	}

	int GetScore()
    {
        return this ->  score;
    }
};
