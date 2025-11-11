#include "gameplay.h"

namespace GoBallGo
{
	void gameplay(SCREENS& currentScreen)
	{
		//Init
		static Player player = initPlayer();

		static Wall wall[MAX_WALLS_IN_SCREEN] = {};

		static Texture2D backGround = LoadTexture("res/img/pixel_art_gradas.png");
		static Texture2D midGround = LoadTexture("res/img/pixel_art_corners.png");
		static Texture2D foreGround = LoadTexture("res/img/pixel_art_pasto.png");

		static float scrollingBack = 0.0f;
		static float scrollingMid = 0.0f;
		static float scrollingFore = 0.0f;

		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
			wall[i] = initWall();

		while (!WindowShouldClose() && player.isAlive)
		{
			GameplayStructure::update(currentScreen, player, wall, backGround, midGround, foreGround);

			GameplayStructure::draw(player, wall, backGround, midGround, foreGround);
		}

		UnloadTexture(backGround);
		UnloadTexture(midGround);
		UnloadTexture(foreGround);
	}
}

namespace GameplayStructure
{
	static float scrollingBack = 0.0f;
	static float scrollingMid = 0.0f;
	static float scrollingFore = 0.0f;

	void update(SCREENS& currentScreen, GoBallGo::Player& player, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround)
	{
		scrollingBack -= 10.0f * GetFrameTime();
		scrollingMid -= 50.0f * GetFrameTime();
		scrollingFore -= 100.0f * GetFrameTime();

		if (scrollingBack <= -backGround.width * 2)
			scrollingBack = 0;
		if (scrollingMid <= -midGround.width * 2)
			scrollingMid = 0;
		if (scrollingFore <= -foreGround.width * 2)
			scrollingFore = 0;

		playerMovment(player);

		playerScreenCollision(player);

		wallUpdate(wall, player);

		if (!player.isAlive)
			currentScreen = MENU;
	}

	void draw(GoBallGo::Player& player, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround)
	{
		BeginDrawing();

		ClearBackground(DARKGREEN);

		DrawTextureEx(backGround, { scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(backGround, { backGround.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

		DrawTextureEx(midGround, { scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(midGround, { midGround.width * 2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

		DrawTextureEx(foreGround, { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(foreGround, { foreGround.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

		DrawRectangle(static_cast<int>(player.x), static_cast<int>(player.y), static_cast<int>(player.w), static_cast<int>(player.h), RED);
		drawWall(wall);

		//end Draw
		EndDrawing();
	}
}
