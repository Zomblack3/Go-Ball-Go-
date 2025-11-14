#include "gameplay.h"

#include <iostream>

#include "windowManagment.h"

namespace GoBallGo
{
	void gameplay(SCREENS& currentScreen, bool& isMusicOn, bool& wasMusicOn)
	{
		Player player = initPlayer();
		Player player2 = initPlayer();

		Wall wall[MAX_WALLS_IN_SCREEN] = {};

		Vector2 mouse = { };

		Button gameModeButtonSingleplayer = initButton(screenWidth / 2.0f, screenHeight / 3.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button gameModeButtonMultiplayer = initButton(screenWidth / 2.0f, screenHeight / 2.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);

		gameModeButtonSingleplayer.x -= gameModeButtonSingleplayer.w / 2.0f;
		gameModeButtonMultiplayer.x -= gameModeButtonMultiplayer.w / 2.0f;

		Texture2D backGround = LoadTexture("res/img/pixel_art_gradas.png");
		Texture2D midGround = LoadTexture("res/img/pixel_art_corners.png");
		Texture2D foreGround = LoadTexture("res/img/pixel_art_pasto.png");
		player.texture = LoadTexture("res/img/player.png");
		player2.texture = LoadTexture("res/img/player.png");

		for (int i = 0; i < MAX_WALLS_IN_SCREEN; i++)
			wall[i] = initWall();

		GameplayStructure::selectGameMode(player, player2, gameModeButtonSingleplayer, gameModeButtonMultiplayer, mouse);

		while (!WindowShouldClose() && player.isAlive)
		{
			GameplayStructure::update(currentScreen, player, player2, wall, backGround, midGround, foreGround, isMusicOn, wasMusicOn);

			GameplayStructure::draw(player, player2, wall, backGround, midGround, foreGround);
		}

		UnloadTexture(backGround);
		UnloadTexture(midGround);
		UnloadTexture(foreGround);
		UnloadTexture(player.texture);
		UnloadTexture(player.texture);

		player.isActive = false;
		player2.isActive = false;

		player.isAlive = true;
		player2.isAlive = true;
	}
}

namespace GameplayStructure
{
	static float scrollingBack = 0.0f;
	static float scrollingMid = 0.0f;
	static float scrollingFore = 0.0f;

	void selectGameMode(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Button gameModeButtonSingleplayer, GoBallGo::Button gameModeButtonMultiplayer, Vector2& mouse)
	{
		const int buttonsAmount = 2;

		Texture2D background = LoadTexture("res/img/gameModeSelectionBackground.png");
		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");

		gameModeButtonSingleplayer.texture = buttonsTexture;
		gameModeButtonMultiplayer.texture = buttonsTexture;

		std::string buttonsTexts[buttonsAmount] = { "SINGLEPLAYER", "MULTIPLAYER" };

		int buttonsTextsLenghts[buttonsAmount] = { };

		for (int i = 0; i < buttonsAmount; i++)
			buttonsTextsLenghts[i] = MeasureText(buttonsTexts[i].c_str(), GoBallGo::normalFontSize);

		while (!gameModeButtonSingleplayer.isPressed && !gameModeButtonMultiplayer.isPressed)
		{
			mouse = GetMousePosition();

			GoBallGo::mouseSelection(mouse, gameModeButtonSingleplayer);
			GoBallGo::mouseSelection(mouse, gameModeButtonMultiplayer);

			if (gameModeButtonSingleplayer.isPressed)
				player.isActive = true;

			if (gameModeButtonMultiplayer.isPressed)
			{
				player.isActive = true;
				player2.isActive = true;
			}

			BeginDrawing();

			ClearBackground(DARKGREEN);

			DrawTexture(background, 0, 0, WHITE);

			DrawTexture(gameModeButtonSingleplayer.texture, static_cast<int>(gameModeButtonSingleplayer.x), static_cast<int>(gameModeButtonSingleplayer.y), gameModeButtonSingleplayer.buttonTint);
			DrawTexture(gameModeButtonMultiplayer.texture, static_cast<int>(gameModeButtonMultiplayer.x), static_cast<int>(gameModeButtonMultiplayer.y), gameModeButtonMultiplayer.buttonTint);

			DrawText(buttonsTexts[0].c_str(), static_cast<int>((gameModeButtonSingleplayer.x + gameModeButtonSingleplayer.w / 2.0f) - (buttonsTextsLenghts[0] / 2.0f)), static_cast<int>(gameModeButtonSingleplayer.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, gameModeButtonSingleplayer.textColor);
			DrawText(buttonsTexts[1].c_str(), static_cast<int>((gameModeButtonMultiplayer.x + gameModeButtonMultiplayer.w / 2.0f) - (buttonsTextsLenghts[1] / 2.0f)), static_cast<int>(gameModeButtonMultiplayer.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, gameModeButtonMultiplayer.textColor);

			EndDrawing();
		}
	}

	void update(SCREENS& currentScreen, GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround, bool& isMusicOn, bool& wasMusicOn)
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

		GoBallGo::playerMovment(player, player2);

		GoBallGo::playerScreenCollision(player);

		if (player2.isActive)
			GoBallGo::playerScreenCollision(player2);

		GoBallGo::wallUpdate(wall);
		GoBallGo::wallUpdate(wall);

		for (int i = 0; i < GoBallGo::MAX_WALLS_IN_SCREEN; i++)
		{
			GoBallGo::wallPlayerCollision(wall[i], player);
			GoBallGo::wallPlayerCollision(wall[i], player2);
		}

		if (!player.isAlive || !player2.isAlive)
		{
			currentScreen = MENU;

			isMusicOn = wasMusicOn;
		}
	}

	void draw(GoBallGo::Player& player, GoBallGo::Player& player2, GoBallGo::Wall wall[], Texture2D& backGround, Texture2D& midGround, Texture2D& foreGround)
	{
		Vector2 bgPos = { };
		Vector2 mgPos = { };
		Vector2 fgPos = { };

		BeginDrawing();

		ClearBackground(DARKGREEN);

		DrawTextureEx(backGround, { scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(backGround, { backGround.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

		DrawTextureEx(midGround, { scrollingMid, 1000 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(midGround, { midGround.width * 2 + scrollingMid, 1000 }, 0.0f, 2.0f, WHITE);

		DrawTextureEx(foreGround, { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
		DrawTextureEx(foreGround, { foreGround.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

		if (player.isActive && player.isAlive)
			DrawTexture(player.texture, static_cast<int>(player.x), static_cast<int>(player.y), WHITE);

		if (player2.isActive && player2.isAlive)
			DrawTexture(player2.texture, static_cast<int>(player2.x), static_cast<int>(player2.y), RED);
		
		drawWall(wall);

		EndDrawing();
	}
}
