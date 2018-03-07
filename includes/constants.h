#ifndef GAME_CONSTANTS
#define GAME_CONSTANTS

/**
 * Global header file for global game constants
 */

const unsigned int	MAX_NUM_GAME_OBJECTS = 10000;
const unsigned int	NUM_LIVES = 2;

const unsigned int	MAX_NUM_ROCKETS = 32;
const unsigned int	MAX_NUM_BOMBS = 32;
const unsigned int	POINTS_PER_ALIEN = 100;
const float			FIRE_TIME_INTERVAL = .5f;
const float			BOMB_TIME_INTERVAL = 1.25f;
const float			PLAYER_SPEED = 160.0f;
const float			ROCKET_SPEED = 160.0f;
const float			ALIEN_SPEED = 40.0f;
const float			BOMB_SPEED = 120.0f;
const int           SPRITE_SIDE = 32;
const double        X_MAPSCALE = 1/SPRITE_SIDE;
const double        Y_MAPSCALE = 1/SPRITE_SIDE;
		// speed of the game; it is increased each time all the aliens are hit
							// it is also the score multiplier
#endif // GAME_CONSTANTS
