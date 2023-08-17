#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
#include "Primitives.h"
#include "TextureManager.h"

constexpr int kScrollSpeed = 2; // The Obstacles will scroll 2 pixels per frame

class Obstacle // Not a GameObject.
{
public:
	Obstacle(const SDL_FRect dst, bool hasImage = false, const SDL_Rect src = {0,0,0,0}, const char* key = "");
	~Obstacle();
	void Update();
	void Render();
	const SDL_FPoint GetPos() { return m_pos; }
	const SDL_FPoint SetPos(SDL_FPoint new_pos) {  m_pos = new_pos; }
	bool Has_Image() { return m_hasImage; }
private:
	bool m_hasImage;
	Image* m_pImage; // Pointer to visual component.
	SDL_FPoint m_pos; // Position on screen.
	
	

};

#endif