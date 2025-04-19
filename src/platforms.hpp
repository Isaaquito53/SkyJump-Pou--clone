#pragma once
#include "utilities.hpp"

/* ----------------------------------------------------------------------- */
// Platform class:
class Platform
{
public:
	Platform();
	Platform(int x, int y, int scale, bool coin);
	~Platform() {};

	SDL_FRect m_rect;		// platform
	bool m_coin = false;	// has it a coin?
private:
	int m_scale = 50;		// scale
	bool m_boost = false;	// is it a boost platform?
	bool m_move = false;	// is it a moving platform?
	bool m_cloud = false;	// will it disappear when jumping on it?
	bool m_plane = false;	// will it move from left to right without stopping?
};
/* ----------------------------------------------------------------------- */