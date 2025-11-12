#pragma once

#include "raylib.h" 

namespace GoBallGo
{
	struct Player
	{
		float x = 0.0f;
		float y = 0.0f;
		float h = 0.0f;
		float w = 0.0f;
		float jump = 0.0f;
		float jumpCicles = 0.0f;

		bool isActive = false;
		bool isAlive = true;
		bool isJumping = false;
		bool isWinner = false;

		int currentPlayerLives = 0;
		int points = 0;

		Texture2D texture = { };
	};

	const int MAX_PLAYER_POINTS = 5;

	const float PLAYER_WIDTH = 45.0f;
	const float PLAYER_HEIGHT = 45.0f;
	const float MAX_JUMP_CICLES = 10.0f;
	const float MAX_PLAYER_JUMP_FORCE = 150000.0f;

	Player initPlayer();

	void playerMovment(Player& player, Player& player2);
	void playerScreenCollision(Player& player);
	void playerClamp(Player& player);
}