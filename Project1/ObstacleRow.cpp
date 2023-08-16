#include "ObstacleRow.h"
#include "RenderManager.h"
#include <cstdlib>
#include <ctime>

#include<iostream> //remove later

ObstacleRow::ObstacleRow() : m_gapCtr(0), m_gapMax(3)
{
	// Create the vector now.     
	for (int i = 0; i < 9; i++)
	{
		m_obstacles.push_back(new Obstacle({ 128.0f * i, 402.0f, 128.0f, 128.0f }));
	}
}

bool ObstacleRow::Update(SDL_FRect& Player)
{
	srand(time(NULL));
	//m_obstacles[0];
	int playerTextureWidth, playerTextureHeight;
	SDL_Texture* Player_Temp = TEMA::GetTexture("player");
	SDL_QueryTexture(Player_Temp, nullptr, nullptr, &playerTextureWidth, &playerTextureHeight);
	//std::cout << playerTextureHeight << std::endl;
	for (const auto obstacle : m_obstacles)
	{
		//Player_Temp
		if (Player.x < obstacle->GetPos().x + 64 &&
			Player.x + Player.w > obstacle->GetPos().x &&
			Player.y < obstacle->GetPos().y + 64 &&
			Player.y + Player.h > obstacle->GetPos().y)
		{

			std::cout << "Death!\n";
			return 1;
			
			// Collision detected between player and obstacle
			// Handle collision logic here
		}
	}
	// Check if first obstacle goes off-screen
	if (m_obstacles[0]->GetPos().x <= -128.0f) // -128.0f is hardcoded
	{
		// pop the first vector element off.
		delete m_obstacles[0]; // or delete m_obstacles.front()
		m_obstacles[0] = nullptr;
		m_obstacles.erase(m_obstacles.begin()); // pop.front()

		// add a new element to the end
		if (m_gapCtr++ % m_gapMax == 0) // need to render an obstacle image 			//m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }, true));
		{
			int randomObstacle = rand() % 3;
			if (randomObstacle == 0) {
				m_obstacles.push_back(new Obstacle({ 1020.0f, 550.0f, 64.0f, 64.0f }, true, { 0, 0, 320, 170 }, "missles"));
			}

			else if (randomObstacle == 1) {
				m_obstacles.push_back(new Obstacle({ 1020.0f, 600.0f, 64.0f, 64.0f }, true, { 0, 0, 1184, 1184 }, "blade"));
			}

			else {
				m_obstacles.push_back(new Obstacle({ 1020.0f, 500.0f, 120.0f, 40.0f }, true, { 0, 0, 650, 240 }, "bomb"));
			}
		}
		else
			m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }));
	}
	// Scroll the obstacles
	//if(Player.)
	for (const auto obstacle : m_obstacles)
		obstacle->Update();
	return 0;
}
void ObstacleRow::Update()
{
	srand(time(NULL));
	// Check if first obstacle goes off-screen
	if (m_obstacles[0]->GetPos().x <= -128.0f) // -128.0f is hardcoded
	{
		// pop the first vector element off.
		delete m_obstacles[0]; // or delete m_obstacles.front()
		m_obstacles[0] = nullptr;
		m_obstacles.erase(m_obstacles.begin()); // pop.front()

		// add a new element to the end
		if (m_gapCtr++ % m_gapMax == 0) // need to render an obstacle image 			//m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }, true));
		{
			int randomObstacle = rand() % 3;
			if (randomObstacle == 0) {

				m_obstacles.push_back(new Obstacle({ 1020.0f, 550.0f, 64.0f, 64.0f }, true, { 0, 0, 320, 170 }, "missles"));
			}

			else if (randomObstacle == 1) {
				m_obstacles.push_back(new Obstacle({ 1020.0f, 600.0f, 64.0f, 64.0f }, true, { 0, 0, 1184, 1184 }, "blade"));

			}

			else {
				m_obstacles.push_back(new Obstacle({ 1020.0f, 500.0f, 120.0f, 40.0f }, true, { 0, 0, 650, 240 }, "bomb"));

			}

		}
		else
			m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }));
	}
	// Scroll the obstacles
	for (const auto obstacle : m_obstacles)
		obstacle->Update();
}

void ObstacleRow::Render()
{
	// Blue line under obstacles.
	//SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 255, 0, 255);
	//SDL_RenderDrawLine(REMA::GetRenderer(), 0, 513, 1024, 512);
	// Render the obstacles.
	for (const auto obstacle : m_obstacles)
	{
		obstacle->Render();
	}
}