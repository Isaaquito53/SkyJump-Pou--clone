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
	// 1: 96, 2: 216, 3: 336, 4: 456, 5: 540
	for (int i = 1; i < m_nPlats; i++) {
		Platform pl = Platform(rand() % (WINDOW_WIDTH - m_platsScale), h * i - h/5 , m_platsScale);
		m_randPlats.push_back(pl);
	}
	Platform startPl(0, WINDOW_HEIGHT - h/2, WINDOW_WIDTH);
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
		int discardNPlats = m_nPlats - 1 - platColl;
		cout << discardNPlats << " platforms should be discarded!" << endl;
		for (int i = 0; i < discardNPlats; i++)
			m_randPlats.pop_back();
		int h = WINDOW_HEIGHT / m_nPlats;
		// move correctly the rest of the platforms
		for (Platform& pl : m_randPlats) {
			pl.m_rect.y += h * discardNPlats;
		}
		// generate as many platforms as has been discarded
		for (int i = discardNPlats; i > 0; i--) {
			Platform pl = Platform(rand() % (WINDOW_WIDTH - m_platsScale), h * i - h / 5, m_platsScale);
			cout << "New platform at: " << h * i - h / 5 << endl;
			m_randPlats.push_front(pl);
		}
		cout << "There are " << m_randPlats.size() << " platforms." << endl;
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
		// draw the platforms
		for (Platform pl : m_randPlats) {
			SDL_SetRenderDrawColor(m_rend, 255, 255, 255, 255);
			SDL_RenderFillRect(m_rend, &pl.m_rect);
		}
		// draw the player
		SDL_SetRenderDrawColor(m_rend, 180, 180, 180, 255);
		SDL_RenderFillRect(m_rend, &m_player.m_player);
		SDL_RenderPresent(m_rend);
		d++;
		// 75 is the speed of the game
		if (d >= 150) {	
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