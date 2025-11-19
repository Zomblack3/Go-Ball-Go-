#include "wall.h"

#include "raylib.h"

namespace GoBallGo
{
	Wall initWall()
	{
		Wall wall = { };

		wall.x = static_cast<float>(GetScreenWidth());
		wall.y = static_cast<float>(GetRandomValue(static_cast<int>(PLAYER_HEIGHT) * 2, GetScreenHeight()));
		wall.h = static_cast<float>(GetScreenHeight());
		wall.w = PLAYER_WIDTH / 1.5f;
		wall.speedX = WALL_SPEED;

		return wall;
	}

	void wallMovement(Wall& wall)
	{
		wall.x -= wall.speedX * GetFrameTime();
	}

	void changeRandomWall(Wall& wall, int& lastWallPassed)
	{
		if (wall.x + wall.w <= 0.0f)
		{
			wall.x = static_cast<float>(GetScreenWidth());
			wall.y = static_cast<float>(GetRandomValue(static_cast<int>(PLAYER_HEIGHT) * 2, GetScreenHeight()));

			lastWallPassed = 0;
		}
	}

	void wallPlayerCollision(Wall wall, Player& player, Sound deathSound)
	{
		if (wall.x + wall.w >= player.x && wall.x <= player.x + player.w &&
			wall.y + wall.h >= player.y && wall.y <= player.y + player.h)
		{
			player.isAlive = false;

  			PlaySound(deathSound);
		}
	}

	void wallPlayerHasPass(Wall wall[], Player& player, int& lastWallPassed, Sound scoreSound)
	{
		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
		{
			if (i % 2 != 0 && i != lastWallPassed)
			{
				if (player.x > wall[i].x)
				{
					player.points++;

					lastWallPassed = i;
					
					PlaySound(scoreSound);
				}
			}
		}
	}

	void wallUpdate(Wall wall[], int& lastWallPassed)
	{
		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
		{
			wallMovement(wall[i]);
			changeRandomWall(wall[i], lastWallPassed);
			createTopWall(wall);
		}
	}

	void createTopWall(Wall wall[])
	{
		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
		{
			if (i % 2 != 0)
			{
				wall[i].y = 0.0f;
				wall[i].h = wall[i - 1].y - (PLAYER_HEIGHT + PLAYER_HEIGHT * 2);
			}
		}
	}

	bool bottomWallTopWallCollision(Wall& wall1, Wall& wall2)
	{
		if (wall1.x + wall1.w >= wall2.x && wall1.x <= wall2.x + wall2.w &&
			wall1.y + wall1.h >= wall2.y && wall1.y <= wall2.y + wall2.h)
			return true;
		else
			return false;
	}

	void drawWall(Wall wall[])
	{
		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
			DrawRectangle(static_cast<int>(wall[i].x), static_cast<int>(wall[i].y), static_cast<int>(wall[i].w), static_cast<int>(wall[i].h), WHITE);
	}

	void setWallDefault(Wall wall[])
	{
		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
		{
			wall[i].x = static_cast<float>(GetScreenWidth());
			wall[i].y = static_cast<float>(GetRandomValue(static_cast<int>(PLAYER_HEIGHT) * 2, GetScreenHeight()));
			wall[i].h = static_cast<float>(GetScreenHeight());
			wall[i].w = PLAYER_WIDTH / 1.5f;
			wall[i].speedX = WALL_SPEED;
		}
	}
}
