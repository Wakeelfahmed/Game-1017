#include <iostream>
#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(const char* key)
{
	m_backgrounds.reserve(10);// Sets capacity to 10.
	// Instantiate backgrounds and add them to vector.
	m_backgrounds.push_back(new Background({ 0,0,1024,768 }, { 0.0f, 0.0f, 1024.0f, 768.0f }, 1.0f, key));
	m_backgrounds.push_back(new Background({ 0,0,1024,768 }, { 1024.0f, 0.0f, 1024.0f, 768.0f }, 1.0f, key));

	//Midgrounds
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 0.0f, 530.0f, 256.0f,512.0f }, 2.0f, key));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 256.0f, 530.0f, 256.0f,512.0f }, 2.0f, key));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 512.0f, 530.0f, 256.0f,512.0f }, 2.0f, key));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 768.0f, 530.0f, 256.0f,512.0f }, 2.0f, key));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 1024.0f, 530.0f, 256.0f,512.0f }, 2.0f, key));

	//Foregrounds
	m_backgrounds.push_back(new Background({ 1024,512,512,256 }, { 0.0f, 512.0f, 512.0f,256.0f }, 3.0f, key));
	m_backgrounds.push_back(new Background({ 1024,512,512,256 }, { 512.0f, 512.0f, 512.0f,256.0f }, 3.0f, key));
	m_backgrounds.push_back(new Background({ 1024,512,512,256 }, { 1024.0f, 512.0f, 512.0f,256.0f }, 3.0f, key));
}

ScrollingBackground::~ScrollingBackground()
{
	// Clear backgrounds.
	for (auto background : m_backgrounds)
	{
		delete background;
		background = nullptr;
	}
	m_backgrounds.clear();
	m_backgrounds.shrink_to_fit();
}

void ScrollingBackground::Update()
{
	// Update backgrounds.
	for (auto background : m_backgrounds)
	{

		background->Update();
	}
}

void ScrollingBackground::Render()
{
	// Render backgrounds.
	for (auto background : m_backgrounds)
	{

		background->Render();
	}
}

