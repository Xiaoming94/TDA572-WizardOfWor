#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "avancezlib.h"
#include "object_pool.h"

#include <set>


#include "constants.h"

float game_speed = 1.f;
#include "component.h"
#include "game_object.h"
#include "collide_component.h"

#include "projectile.h"
#include "player.h"
#include "enemy.h"

#include "game.h"


int main(int argc, char** argv)
{

	AvancezLib system;

	system.init(640, 480);

	Game game;
	game.Create(&system);
	game.Init();

	float lastTime = system.getElapsedTime();
	while (system.update())
	{
		float newTime = system.getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * game_speed;
		lastTime = newTime;

		game.Update(dt);

		game.Draw();
	}

	// clean up
	game.Destroy();
	system.destroy();

	return 0;
}

