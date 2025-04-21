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
	int Jump(list<Platform> &rects);						// manage the constant jump
	void Move(SDL_Event key);								// manage the movement
	int collide(list<Platform> rects);						// manage collisions with platforms
	void platAction(list<Platform>& rects, int col);		// manage the action depending on the type of the plat

	SDL_FRect m_player;										// graphic representation of the player
	int m_score = 0;										// score of the game
	int m_coins = 0;										// amount of coins
private:
	int m_playerScale = 50;									// size of the player
	int m_upDown = 1;										// y orientation of the player
};
/* ----------------------------------------------------------------------- */