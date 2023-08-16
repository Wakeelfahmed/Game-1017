#include "Background.h"

Background::Background(const SDL_Rect src, const SDL_FRect dst, float ss, const char* key) 
	:Image(src, dst, key), m_scrollSpeed(ss)
{
	// Initialize start and end properties.
	m_startX = GetDst()->x; //Initial recording, so it knows where to "bounce back"to
	m_endX = m_startX - GetDst()->w;
}

void Background::Update()
{
	// Check if at end of journey.
	if (GetDst()->x <= m_endX)
		GetDst()->x = m_startX;
	// Scroll the background.
	GetDst()->x -= m_scrollSpeed;
}

void Background::Render()
{
	Image::Render(); // Ask the base class to render instead.
}
