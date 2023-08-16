#ifndef __SCROLLINGBACKGROUND_H__
#define __SCROLLINGBACKGROUND_H__
#include "GameObject.h"
#include "Background.h"
#include <vector>

class ScrollingBackground : public GameObject
{
public:
	ScrollingBackground(const char* key);
	~ScrollingBackground();
	void Update();
	bool Update(SDL_FRect& object1) { return 0; }
	void Render();
private:
	// Add vector of Background pointers.
	std::vector<Background*> m_backgrounds;
};

#endif