#pragma once

#include "player.h"

namespace GoBallGo
{
	struct Wall
	{
		float x;
		float y;
		float w;
		float h;
		float speedX;
	};

	const float DISTANCE_BETWEEN_WALLS = 60.0f;
	const float WALL_SPEED = 250.0f;
	const int MAX_WALLS_IN_SCREEN = 2;

	Wall initWall();
	void wallMovement(Wall& wall);
	void changeRandomWall(Wall& wall, int& lastWallPassed);
	void wallPlayerCollision(Wall wall, Player& player);
	void wallPlayerHasPass(Wall wall[], Player& player, int& lastWallPassed);
	void wallUpdate(Wall wall[], int& lastWallPassed);
	void createTopWall(Wall wall[]);
	bool bottomWallTopWallCollision(Wall& wall1, Wall& wall2);
	void drawWall(Wall wall[]);
	void setWallDefault(Wall wall[]);
}