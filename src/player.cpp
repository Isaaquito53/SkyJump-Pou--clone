#pragma once
#include "player.hpp"

/* ----------------------------------------------------------------------- */
// Player methods:

Player::Player() {
	m_player.x = 400 / 2 - m_playerScale/2;
	m_player.y = 100;
	m_player.w = m_playerScale;
	m_player.h = m_playerScale;
}

Player::Player(int playerScale) {
	m_playerScale = playerScale;
	m_player.x = 400 / 2 - m_playerScale / 2;
	m_player.y = WINDOW_HEIGHT / 2;
	m_player.w = m_playerScale;
	m_player.h = m_playerScale;
}

// -------------------------------> Collision management
bool Player::collide(list<Platform> rects) {
	int i = 0;
	for (Platform rect : rects) {
		// the player only collides if it is above the platform
		if ((m_player.y + m_playerScale >= rect.m_rect.y && m_player.y < rect.m_rect.y + 5) &&
			(m_player.x + m_playerScale >= rect.m_rect.x && m_player.x < rect.m_rect.x + rect.m_rect.w))
		{
			// cout << "Number of platform collided: " << i << endl;
			return true;
		}
		i++;
	}
	return false;
}

// -------------------------------> Player jumping management
bool Player::Jump(list<Platform> rects) {
	m_player.y += m_upDown;		// upDown change the y-orientation of the player
	if (collide(rects) && m_upDown > 0) {
		m_upDown = -m_upDown;
		return true;			// if the player collides with a platform return true
	}
	else if (m_player.y <= WINDOW_HEIGHT / 5)
		m_upDown = -m_upDown;
	return false;
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