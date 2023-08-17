#include <iostream>
#include "States.h"
#include "StateManager.h"
// GameObject includes.
#include "Primitives.h"
#include "PlatformPlayer.h"
#include "Button3.h"
#include "ObstacleRow.h" // Our container for Obstacles
#include "ScrollingBackground.h"
// Remaining managers.
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "FontManager.h"

#include <iostream>
using namespace std;
void State::Update()
{
	for (auto const& i : m_objects)
	{
		if (i.first == "Obstacles") {

			if (i.second->Update(*(m_objects[1].second->GetDst()))) {

				m_objects[1].second->SetEnabled(false);		//Set Player to false
				cout << "Death";
			}
		}
		else
			i.second->Update();
		if (STMA::StateChanging()) return;
	}
	for (auto const& i : m_objects) {
		if (i.first == "Timer") {
			RemoveChild("Timer");
			elapsedTime = SDL_GetTicks() - startTime;
			std::string timeText = "Time " + std::to_string(elapsedTime / 1000);
			AddChild("Timer", new Label("ARCADECLASSIC", 2, -10, timeText.c_str()));
			break;
		}
	}

}
void State::Render()
{
	//AddChild("LoseText", new Label("ARCADECLASSIC", 360, 200, timeText.c_str()));
	for (auto const& i : m_objects)
		i.second->Render();
	if (dynamic_cast<GameState*>(this) && dynamic_cast<PauseState*>(STMA::GetStates().back()))
		return;
	SDL_RenderPresent(REMA::GetRenderer());
}
void State::Exit()
{
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}
void State::AddChild(std::string key, GameObject* object)
{
	m_objects.push_back(pair<string, GameObject*>(key, object));
}

GameObject* State::GetChild(const std::string& key)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == key;
		});
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

template<class T>
T State::GetChild(const std::string& key)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == key;
		});
	if (it != m_objects.end())
	{
		return static_cast<T>(it->second); // Downcasting now done here!
	}
	else return nullptr;
}

void State::RemoveChild(const std::string& key)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == key;
		});
	if (it != m_objects.end())
	{
		delete it->second; // Deallocate GameObject.
		it->second = nullptr; // Wrangle dangle.
		m_objects.erase(it);
		m_objects.shrink_to_fit();
	}
}

// Begin TitleState.
TitleState::TitleState() = default;
void TitleState::Enter()
{
	cout << "Entering TitleState..." << endl;
	FOMA::Load("Assets/Font/ARCADECLASSIC.ttf", "ARCADECLASSIC", 64);
	FOMA::Load("Assets/Font/ka1.ttf", "ka1", 28);

	TEMA::Load("Assets/Image/Background.jpg", "TitleBG");
	AddChild("play", new Image({ 0, 0, 1024, 1024 }, { 0, 0, 1024.0f, 768.0f }, "TitleBG"));

	//AddChild("Line1", new Line({100.0f,100.0f}, {500.0f,500.0f}, {255,255,0,255})); // How to draw a line
	AddChild("TitleText", new Label("ARCADECLASSIC", 1024.0 / 2.0f - 200, 680.0 / 2.0f - 200, "Crazy Kitten", { 255, 0, 0, 255 }));


	AddChild("DeveloperNameText", new Label("ka1", 1024.0 / 2.0f - 120, 768.0 / 2.0f + 350, " By Homeless - Melih Burak Asci", { 204, 102, 0, 255 }));

	FOMA::SetSize("Assets/Font/ka1.ttf", "ka1", 22);
	TEMA::Load("Assets/Image/buttons.png", "PlayButton");
	AddChild("play", new PlayButton({ 0, 105, 200, 105 }, { 412.0f, 470.0f, 200.0f, 50.0f }, "PlayButton"));
	AddChild("PlayButtonText", new Label("ka1", 462.0f, 480.0f, "PLAY", { 0, 0, 0, 255 }));
	AddChild("Exit", new ExitButton({ 0, 105, 200, 105 }, { 412.0f, 540.0f, 200.0f, 50.0f }, "PlayButton"));
	AddChild("ExitButtonText", new Label("ka1", 462.0f, 550, "Exit", { 0, 0, 0, 255 }));

	SOMA::AllocateChannels(16);
	SOMA::Load("Assets/Audio/menumusic.mp3", "menumusic", SOUND_MUSIC);
	SOMA::SetMusicVolume(42);
	SOMA::PlayMusic("menumusic", -1, 2000);
}
void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		STMA::ChangeState(new GameState());
		return;
	}
	State::Update();
}
void TitleState::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(REMA::GetRenderer());
	State::Render();
}
void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
	TEMA::Unload("PlayButton");
	TEMA::Unload("TitleBG");
	SOMA::StopMusic();
	SOMA::Unload("menumusic", SOUND_MUSIC);
	State::Exit();
}
// End TitleState.

// Begin PauseState.
PauseState::PauseState() = default;
void PauseState::Enter()
{
	cout << "Entering PauseState..." << endl;
	AddChild("pauseText", new Label("ARCADECLASSIC", 410, 200, "Paused"));
	AddChild("pauseText", new Label("ARCADECLASSIC", 255, 390, "Press R to Resume"));
}
void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		SOMA::PlaySound("pause");
		STMA::PopState();
		return;
	}
	State::Update();
}
void PauseState::Render()
{
	// First render the GameState
	STMA::GetStates().front()->Render();
	// Now render rest of PauseState
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(REMA::GetRenderer(), &rect);
	State::Render();
}
void PauseState::Exit()
{
	cout << "Exiting PauseState..." << endl;
	State::Exit();
}
// End PauseState.

// Begin GameState.
GameState::GameState() = default;
void GameState::Enter()
{
	cout << "Entering GameState..." << endl;
	FOMA::Load("Assets/Font/ARCADECLASSIC.ttf", "ARCADECLASSIC", 24);
	TEMA::Load("Assets/image/citylights.png", "citylights");
	TEMA::Load("Assets/image/missles.png", "missles");
	TEMA::Load("Assets/image/blade.png", "blade");
	TEMA::Load("Assets/image/bomb.png", "bomb");
	TEMA::Load("Assets/image/player.png", "player");

	AddChild("background", new ScrollingBackground("citylights"));
	AddChild("player", new PlatformPlayer({ 0,0,32,32 }, { 128,576,64,64 }));
	AddChild("Obstacles", new ObstacleRow());
	m_objects[1].second->SetEnabled(true);
	SOMA::SetSoundVolume(32);
	SOMA::SetMusicVolume(16);

	SOMA::Load("Assets/Audio/pause.mp3", "pause", SOUND_SFX);
	SOMA::Load("Assets/Audio/Biscuit.mp3", "Biscuit", SOUND_MUSIC);
	SOMA::SetMusicVolume(20);
	SOMA::PlayMusic("Biscuit", -1, 2000);
	startTime = SDL_GetTicks(); // Get the current time in milliseconds
	elapsedTime = SDL_GetTicks() - startTime;
	std::string timeText = "Time " + std::to_string(elapsedTime / 1000);
	AddChild("Timer", new Label("ARCADECLASSIC", 2, -10, timeText.c_str()));

}
void GameState::Update()
{
	if (m_objects[1].second->GetEnabled() == false)
	{
		STMA::PushState(new LoseState()); // Change to new LoseState
		collision_detected = 1;
	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_X))
	{
		STMA::ChangeState(new TitleState()); // Change to new TitleState
		return;
	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		SOMA::PauseMusic();
		SOMA::PlaySound("pause");
		STMA::PushState(new PauseState()); // Add new PauseState
		return;
	}
	// Update objects first.
	State::Update();
}
void GameState::Render()
{
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(REMA::GetRenderer());
	State::Render();
}
void GameState::Exit()
{
	cout << "Exiting GameState..." << endl;
	SOMA::StopMusic();
	SOMA::Unload("Biscuit", SOUND_MUSIC);
	TEMA::Unload("citylights");
	TEMA::Unload("missles");
	TEMA::Unload("blades");
	TEMA::Unload("bomb");
	TEMA::Unload("player");


	FOMA::Quit();
	State::Exit();
}
void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
	if (collision_detected) {
		RemoveChild("player");
		AddChild("player", new PlatformPlayer({ 0,0,32,32 }, { 128,576,64,64 }));
		m_objects[1].second->SetEnabled(true);
		RemoveChild("Obstacles");
		AddChild("Obstacles", new ObstacleRow());
		collision_detected = 0;
	startTime = SDL_GetTicks(); // Get the current time in milliseconds
	}
	SOMA::ResumeMusic();
}
// End GameState

LoseState::LoseState() = default;
void LoseState::Enter()
{
	cout << "Entering LoseState..." << endl;
	AddChild("LoseText", new Label("ARCADECLASSIC", 360, 200, "Game Over!"));
	AddChild("LoseText", new Label("ARCADECLASSIC", 255, 390, "Press R to Restart"));
}
void LoseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		SOMA::PlaySound("pause");
		STMA::PopState();
		return;
	}
	State::Update();
}
void LoseState::Render()
{
	// First render the GameState
	STMA::GetStates().front()->Render();
	// Now render rest of LoseState
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(REMA::GetRenderer(), &rect);
	State::Render();
}
void LoseState::Exit()
{
	cout << "Exiting LoseState..." << endl;
	State::Exit();
}