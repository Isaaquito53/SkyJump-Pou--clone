#pragma once
#include "platforms.hpp"

/* ----------------------------------------------------------------------- */
// Platforms methods:

Platform::Platform() {
	m_rect.x = 0;	m_rect.y = 0; m_rect.w = 100;	m_rect.h = 25;
}

Platform::Platform(int x, int y, int scale, bool coin) {

	m_rect.x = x;		m_rect.y = y;		m_rect.w = scale;	m_rect.h = scale/4;
	m_coin = coin;
}

/* ----------------------------------------------------------------------- */