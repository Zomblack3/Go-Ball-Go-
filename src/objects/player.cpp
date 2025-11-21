#include "player.h"

#include "raylib.h"

#include <iostream>

#include "game/windowManagment.h"
#include "game/gameplay.h"

using namespace std;

namespace GoBallGo
{
	Player initPlayer()
	{
		Player player = { };

		player.x = static_cast<float>(screenWidth) / 8.0f;
		player.y = static_cast<float>(screenHeight) / 2.0f;
		player.w = PLAYER_WIDTH;
		player.h = PLAYER_HEIGHT;
		player.jump = MAX_PLAYER_JUMP_FORCE;
		player.isAlive = true;
		player.currentPlayerLives = MAX_PLAYER_POINTS;
		player.points = 0;

		return player;
	}

	void playerMovment(Player& player, Player& player2, Sound jumpSound)
	{
		float deltaTime = GetFrameTime();

		if (player.isActive && player.isAlive)
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				player.speedY = -player.jump * deltaTime;

				if (!IsSoundPlaying(jumpSound))
					PlaySound(jumpSound);
			}
			else
			{
				player.speedY += G_FORCE * deltaTime;

				std::cout << player.speedY << std::endl;
			}

			player.y += player.speedY;
		}

		if (player2.isActive && player2.isAlive)
		{
			if (IsKeyPressed(KEY_W))
			{
				player2.speedY = -player2.jump * deltaTime;

				if (!IsSoundPlaying(jumpSound))
					PlaySound(jumpSound);
			}
			else
				player2.speedY += G_FORCE * deltaTime;

			player2.y += player2.speedY;
		}
	}

	void playerScreenCollision(Player& player)
	{
		if (player.y <= 0.0f)
			player.y = 0.0f;
		if (player.y + player.h >= GetScreenHeight())
			player.isAlive = false;
	}

	void setPlayerDefault(Player& player)
	{
		player.x = static_cast<float>(screenWidth) / 8.0f;
		player.y = static_cast<float>(screenHeight) / 2.0f;
		player.w = PLAYER_WIDTH;
		player.h = PLAYER_HEIGHT;
		player.jump = MAX_PLAYER_JUMP_FORCE;
		player.isAlive = true;
		player.currentPlayerLives = MAX_PLAYER_POINTS;
		player.points = 0;
	}
}
