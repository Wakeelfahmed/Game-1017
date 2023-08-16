#ifndef __OBSTACLEROW_H__
#define __OBSTACLEROW_H__
#include "GameObject.h"
#include "Obstacle.h"
#include <vector>

class ObstacleRow : public GameObject
{
public: // Methods.
	ObstacleRow();
	bool Update(SDL_FRect& object1);

	//void Update(const SDL_FPoint& playerPosition, const std::vector<SDL_FPoint>& obstaclePositions) override { return; }

	/*void Update(SDL_FRect& Player) override {
		return;
	}*/
	/*void Update(const SDL_FPoint& playerPosition, const std::vector<SDL_FPoint>& obstaclePositions) override {
		return;
	}*/

	void Update();
	void Render();
	//std::vector<Obstacle*> Get_Obstacles() { return m_obstacles; }

private: // Properties.
	std::vector<Obstacle*> m_obstacles;
	int m_gapCtr, m_gapMax;
};

#endif