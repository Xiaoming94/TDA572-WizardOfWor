#define PLAYER1_SPRITE "assets/WorriorGold.bmp"
#define PROJECTILE_SPRITE "assets/rocket.bmp"

#include "map.h"
bool change_direction = false;

class Game : public GameObject
{
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;

	ObjectPool<Projectile> projectiles_pool;	// used to instantiate projectiles

	Player * player;

	Sprite * life_sprite;
	bool game_over;

	unsigned int score = 0;

    Map * game_map;
public:

	virtual void Create(AvancezLib* system)
	{
		SDL_Log("Game::Create");

		this->system = system;
        game_map = create_standard_map(system);
        for (auto row : game_map -> get_map()){
            for (auto tile : row)
                game_objects.insert(tile);
        }



		player = new Player();
		PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
		player_behaviour->Create(system, player, &game_objects, &projectiles_pool);
		RenderComponent * player_render = new RenderComponent();
		player_render->Create(system, player, &game_objects, PLAYER1_SPRITE );

		player->Create();
		player->AddComponent(player_behaviour);
		player->AddComponent(player_render);
		player->AddReceiver(this);
		game_objects.insert(player);

		projectiles_pool.Create(30);
		for (auto projectile = projectiles_pool.pool.begin(); projectile != projectiles_pool.pool.end(); projectile++)
		{
			ProjectileBehaviourComponent * behaviour = new ProjectileBehaviourComponent();
			behaviour->Create(system, *projectile, &game_objects);
			RenderComponent * render = new RenderComponent();
			render->Create(system, *projectile, &game_objects, PROJECTILE_SPRITE);
			(*projectile)->Create();
			(*projectile)->AddComponent(behaviour);
			(*projectile)->AddComponent(render);
		}


		life_sprite = system->createSprite(PLAYER1_SPRITE);
		score = 0;

	}

	virtual void Init()
	{
		player->Init();

		enabled = true;
		game_over = false;
	}

	virtual void Update(float dt)
	{
		if (IsGameOver())
			dt = 0.f;

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Update(dt);
	}

	virtual void Draw()
	{
		char msg[1024];
		sprintf(msg, "%07d", Score());
		system->drawText(300, 32, msg);
		sprintf(msg, "bonus: %.1fX", game_speed);
		system->drawText(510, 32, msg);

		for (int i = 0; i < player->lives; i++)
			life_sprite->draw(i*36+20, 16);

		if (IsGameOver())
		{
			sprintf(msg, "*** G A M E  O V E R ***");
			system->drawText(250, 8, msg);
		}
	}

	virtual void Receive(Message m)
	{
		if (m == GAME_OVER)
			game_over = true;

		if (m == ALIEN_HIT)
			score += POINTS_PER_ALIEN * game_speed;
	}


	bool IsGameOver()
	{
		return game_over;
	}

	unsigned int Score()
	{
		return score;
	}

	virtual void Destroy()
	{
		SDL_Log("Game::Destroy");

		for (auto go = game_objects.begin(); go != game_objects.end(); go++)
			(*go)->Destroy();

		life_sprite->destroy();

		projectiles_pool.Destroy();
		delete player;
		delete game_map;
	}
};
