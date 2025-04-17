#pragma once
#include "utilities.hpp"
#include "platforms.hpp"

/* ----------------------------------------------------------------------- */
// Player class:
class Player
{
public:
	Player();
	Player(int playerScale);
	int Jump(list<Platform> rects);			// manage the constant jump
	void Move(SDL_Event key);					// manage the movement
	int collide(list<Platform> rects);			// manage collisions with platforms

	SDL_FRect m_player;							// graphic representation of the player
private:
	int m_playerScale = 50;						// size of the player
	int m_upDown = 1;							// y orientation of the player
};
/* ----------------------------------------------------------------------- */