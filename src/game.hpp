#pragma once
#include "utilities.hpp"
#include "player.hpp"

/* ----------------------------------------------------------------------- */
// Game class:
class Game
{
public:
	void GameInit();					// init the game
	void GameLoop();					// manage the game loop
	void ManageEvents();				// manage the SDL events (key pressed)
	void PlayerProgress();

private:
	SDL_Window* m_win;					// window of the game
	SDL_Renderer* m_rend;				// render of the game
	SDL_Event m_e;						// events of the game
	bool m_run = true;					// if false the game will stop
	Player m_player;					// player
	list<Platform> m_randPlats;			// list of random platforms
	int m_nPlats = 5;					// number of platforms in screen
	int m_platsScale = 100;				// scale of the platforms
};
/* ----------------------------------------------------------------------- */