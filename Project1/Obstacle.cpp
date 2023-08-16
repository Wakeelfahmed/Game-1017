#include "Obstacle.h"
#include "RenderManager.h"

Obstacle::Obstacle(const SDL_FRect dst, bool hasImage, const SDL_Rect src, const char* key)
	:m_hasImage(hasImage), m_pImage(nullptr)
{
	m_pos = { dst.x, dst.y };
	if (m_hasImage)
	{
		m_pImage = new Image(src, dst, key);
		// Create (dynamically using new keyword) a new obstacle based on an image/sprite sheet and pass parameters down
		// You will get plenty of hints in outline. This is for you to do.
	}
}

Obstacle::~Obstacle()
{
	if (m_hasImage)
	{
		delete m_pImage;
		m_pImage = nullptr;
	}
}

void Obstacle::Update()
{
	m_pos.x -= kScrollSpeed;
	if (m_hasImage)
	{
		// Update the image's dest rectangle
		m_pImage->GetDst()->x -= kScrollSpeed;
	}
}

void Obstacle::Render()
{
	//SDL_Rect m_dst = { m_pos.x, m_pos.y, 128, 128 }; // Temporary. Not needed for A@
	SDL_FRect m_dst = { m_pos.x, m_pos.y, 320, 170 }; //Place holder, not needed for A2
	SDL_Rect m_src = { 0, 0, 320, 170 }; //Place holder, not needed for A2
	if (m_hasImage)
	{
		// Obstacle should be rendered
		// render the image
		 //SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture("missles"), &m_src, &m_dst);
		m_pImage->Render();
		// Temporary primitive box for now

		//SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
		//SDL_RenderFillRect(REMA::GetRenderer(), &m_dst);
	}
	//SDL_SetRenderDrawColor(REMA::GetRenderer(), 64, 0, 255, 255);
	//SDL_RenderDrawRect(REMA::GetRenderer(), &m_dst);
}
