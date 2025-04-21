#pragma once
#include "game.hpp"

/* ----------------------------------------------------------------------- */
// Game methods:

void Game::GameInit(){
	// init the game with the name, size of window/render, window and render
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("SkyJump", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_win, &m_rend);

	m_player = Player(30);				// create a player

	int h = WINDOW_HEIGHT / m_nPlats;

	srand(time(NULL));
	
	// generate first platforms
	for (int i = 1; i < m_nPlats; i++) {
		Platform pl = Platform(rand() % (WINDOW_WIDTH - m_platsScale), h * i - h/5 , m_platsScale);
		m_randPlats.push_back(pl);
	}
	Platform startPl(0, WINDOW_HEIGHT - h/2, WINDOW_WIDTH);
	startPl.StartPlatform();
	m_randPlats.push_back(startPl);
}

void Game::ManageEvents() {
	while (SDL_PollEvent(&m_e)) {
		// if you click the cross button the game loop stops
		if (m_e.type == SDL_EVENT_QUIT) {	
			cout << "F";
			m_run = false;
		}
		// manage all the player movements
		if (m_e.type == SDL_EVENT_KEY_DOWN || m_e.type == SDL_EVENT_MOUSE_MOTION) {	
			m_player.Move(m_e);
		}
	}
}

void Game::PlayerProgress() {
	int platColl = m_player.Jump(m_randPlats);
	// if the player has collided with a platform...
	if (platColl != -1) {
		// discard all the platforms below the one you collided
		int discardNPlats = m_randPlats.size() - 1 - platColl;
		for (int i = 0; i < discardNPlats; i++) {
			m_randPlats.pop_back();
			m_player.m_score++;
		}
		// execute the action of the platform you collided (example: delete the platform if it was a cloud)
		m_player.platAction(m_randPlats, platColl);
		// move correctly the rest of the platforms
		int h = WINDOW_HEIGHT / m_nPlats;
		int addNPlats = m_nPlats - 1 - platColl;
		for (Platform& pl : m_randPlats) {
			pl.m_rect.y += h * addNPlats;
		}
		// add an amount of platforms equal to the amount of platforms below the one you collided
		for (int i = addNPlats; i > 0; i--) {
			Platform pl = Platform(rand() % (WINDOW_WIDTH - m_platsScale), h * i - h / 5, m_platsScale);
			m_randPlats.push_front(pl);
		}
	}
}

void Game::DrawScore() {
	SDL_SetRenderDrawColor(m_rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(m_rend, 2., 2.);
	// display the score and coins 
	string score = "Score: " + to_string(m_player.m_score);
	const char *cscore = score.c_str();
	SDL_RenderDebugText(m_rend, 5, 5, cscore);
	string coins = to_string(m_player.m_coins);
	const char* ccoins = coins.c_str();
	SDL_RenderDebugText(m_rend, 5, 15, ccoins);
	SDL_SetRenderScale(m_rend, 1., 1.);
}

void Game::DrawPlatforms() {
	for (Platform pl : m_randPlats) {
		// if the platform has coin==true, draw a coin above it
		if (pl.m_coin) {
			SDL_SetRenderDrawColor(m_rend, 255, 255, 90, 255);
			SDL_FRect coin;
			coin.x = pl.m_rect.x + pl.m_rect.w / 2 - pl.m_rect.h / 2;
			coin.y = pl.m_rect.y - pl.m_rect.h;
			coin.w = pl.m_rect.h;	coin.h = pl.m_rect.h;
			SDL_RenderFillRect(m_rend, &coin);
		}
		// if the platform has cloud==true, draw it white
		if (pl.m_cloud)
			SDL_SetRenderDrawColor(m_rend, 255, 255, 255, 255);
		else
			SDL_SetRenderDrawColor(m_rend, 200, 200, 200, 255);
		SDL_RenderFillRect(m_rend, &pl.m_rect);
	}
}

void Game::GameLoop() {

	int d = 0;					// set delta time to 0
	float updownPlayer = 1;		// set the y-orientation of the player to go down

	while (m_run) {
		// manage events
		ManageEvents();	
		// update the screen
		SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);
		SDL_RenderClear(m_rend);
		DrawPlatforms();
		// draw the player
		SDL_SetRenderDrawColor(m_rend, 180, 180, 180, 255);
		SDL_RenderFillRect(m_rend, &m_player.m_player);
		// draw score
		DrawScore();
		// render all
		SDL_RenderPresent(m_rend);
		d++;
		if (d >= GAME_SPEED) {	
			d = 0;
			PlayerProgress();
		}
	}
}

/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
// MAIN:

int main() {
	Game game;
	game.GameInit();
	game.GameLoop();
	return 0;
}

/* ----------------------------------------------------------------------- */