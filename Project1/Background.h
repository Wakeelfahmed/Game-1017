#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__
#include "Primitives.h"

class Background : public Image
{
public:
	Background(const SDL_Rect src, const SDL_FRect dst, float ss, const char* key);
	void Update();
	void Render();
private:
	float m_scrollSpeed, m_startX, m_endX;
};

#endif