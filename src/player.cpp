#pragma once
#include "player.hpp"

/* ----------------------------------------------------------------------- */
// Player methods:

Player::Player() {
	m_player.x = 400 / 2 - m_playerScale/2;
	m_player.y = WINDOW_HEIGHT-100;
	m_player.w = m_playerScale;
	m_player.h = m_playerScale;
	m_score = 0;
	m_coins = 0;
}

Player::Player(int playerScale) {
	m_playerScale = playerScale;
	m_player.x = 400 / 2 - m_playerScale / 2;
	m_player.y = WINDOW_HEIGHT / 2;
	m_player.w = m_playerScale;
	m_player.h = m_playerScale;
	m_score = 0;
	m_coins = 0;
}

// -------------------------------> Collision management
int Player::collide(list<Platform> rects) {
	int i = 0;
	for (Platform rect : rects) {
		// the player only collides if it is above the platform
		if ((m_player.y + m_playerScale >= rect.m_rect.y && m_player.y < rect.m_rect.y + 5) &&
			(m_player.x + m_playerScale >= rect.m_rect.x && m_player.x < rect.m_rect.x + rect.m_rect.w))
		{
			return i;
		}
		i++;
	}
	return -1;
}

// -------------------------------> Action depending on the type of platform
void Player::platAction(list<Platform>& rects, int coll) {
	// search for the col-th element on the rects list
	auto plat = rects.begin();
	advance(plat, coll);

	if (plat->m_coin) {
		m_coins++;
		plat->m_coin = false;
	}

	if (plat->m_cloud)
		rects.remove(*plat);
}


// -------------------------------> Player jumping management
int Player::Jump(list<Platform> &rects) {
	m_player.y += m_upDown;		// upDown change the y-orientation of the player
	int coll = collide(rects);
	// if the player collide with a platform, return the number of this platform
	if (coll != -1 && m_upDown > 0) {
		m_upDown = -m_upDown;
		return coll;				
	}
	else if (m_player.y <= WINDOW_HEIGHT / 5)
		m_upDown = -m_upDown;
	return -1;
}

// -------------------------------> Player movement management
void Player::Move(SDL_Event e) {
	float discard = .0;
	if (e.type == SDL_EVENT_KEY_DOWN)
	{
		switch (e.key.scancode)
		{
		// left key --> move to left
		case SDL_SCANCODE_LEFT:						
			m_player.x = m_player.x - m_playerScale/5;
			break;
		// right key --> move to right
		case SDL_SCANCODE_RIGHT:					
			m_player.x = m_player.x + m_playerScale / 5;
			break;
		}
	}
	// manage movement with mouse (it isn't polished!!!)
	else
		SDL_GetMouseState(&m_player.x, &discard);

	// if the player goes out of the bounds it will return to the other side
	if (m_player.x + m_player.w / 2 > WINDOW_WIDTH)
		m_player.x = 0;
	else if (m_player.x + m_player.w / 2 < 0)
		m_player.x = WINDOW_WIDTH - m_player.w;
}

/* ----------------------------------------------------------------------- */