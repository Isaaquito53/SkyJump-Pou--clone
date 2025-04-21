#pragma once
#include "platforms.hpp"

/* ----------------------------------------------------------------------- */
// Platforms methods:

Platform::Platform() {
	m_rect.x = 0;	m_rect.y = 0; m_rect.w = 100;	m_rect.h = 25;
}

Platform::Platform(int x, int y, int scale) {

	m_rect.x = x;		m_rect.y = y;		m_rect.w = scale;	m_rect.h = scale/4;
	m_coin = rand() % 2;					m_cloud = rand() % 2;
}

void Platform::StartPlatform() {
	m_coin = false;		m_cloud = false;
}

// this overload method is required to remove a platform by index from the platform list
bool Platform::operator==(Platform const&plat) const {
	if (m_rect.x == plat.m_rect.x && m_rect.y == plat.m_rect.y && m_rect.w == plat.m_rect.w)
		return true;
	return false;
}

/* ----------------------------------------------------------------------- */