#include "tutorial.h"

namespace GoBallGo
{
	void tutorial(SCREENS& currentScreen, Sound& music, bool isMusicOn)
	{
		Button exitButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 10), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);

		Texture2D background = LoadTexture("res/img/tutorial_background.png");
		Texture2D playerTexture = LoadTexture("res/img/player.png");
		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");

		Vector2 mouse = { };

		Sound buttonsChangeStateSound = LoadSound("res/audio/button_sound.wav");

		exitButton.x -= exitButton.w / 2.0f;
		exitButton.texture = buttonsTexture;
		exitButton.changeStateSound = buttonsChangeStateSound;

		while (!WindowShouldClose() && !exitButton.isPressed)
		{
			TutorialStructure::update(mouse, exitButton);

			TutorialStructure::draw(exitButton, background, playerTexture);

			playGameMusic(music, isMusicOn);
		}

		if (exitButton.isPressed)
			currentScreen = MENU;

		UnloadTexture(background);
		UnloadTexture(playerTexture);

		UnloadSound(buttonsChangeStateSound);
	}
}

namespace TutorialStructure
{
	void update(Vector2& mouse, GoBallGo::Button& exitButton)
	{
		mouse = GetMousePosition();

		GoBallGo::mouseSelection(mouse, exitButton);
	}

	void draw(GoBallGo::Button exitButton, Texture2D backrgound, Texture2D player)
	{
		Vector2 lineOneStartingPos = { (GoBallGo::screenWidth / 2), (GoBallGo::screenHeight / 8) - 30 };
		Vector2 lineOneEndingPos = { (GoBallGo::screenWidth / 2), GoBallGo::screenHeight / 2 };
		Vector2 lineTwoStartingPos = { (GoBallGo::screenWidth / 10) - 10, (GoBallGo::screenHeight / 2) };
		Vector2 lineTwoEndingPos = { GoBallGo::screenHeight + (GoBallGo::screenHeight / 8) + 60, (GoBallGo::screenHeight / 2) };

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(backrgound, 0, 0, WHITE);

		DrawTexture(player, (GoBallGo::screenWidth / 2) - (GoBallGo::screenWidth / 4) - player.width * 3, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4), WHITE);

		DrawText("PLAYER", (GoBallGo::screenWidth / 2) - (GoBallGo::screenWidth / 4) + 35, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) - 50, GoBallGo::titlesFontSize, DARKBLUE);
		DrawText("This will be your character", (GoBallGo::screenWidth / 2) - (GoBallGo::screenWidth / 4) - 60, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4), GoBallGo::normalFontSize, BLACK);
		DrawText("and you have to not crash it", (GoBallGo::screenWidth / 2) - (GoBallGo::screenWidth / 4) - 65, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 30, GoBallGo::normalFontSize, BLACK);
		DrawText("into the goalposts or it will be", (GoBallGo::screenWidth / 2) - (GoBallGo::screenWidth / 4) - 75, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 60, GoBallGo::normalFontSize, BLACK);
		DrawText("game over", (GoBallGo::screenWidth / 2) - (GoBallGo::screenWidth / 4) + 45, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 90, GoBallGo::normalFontSize, BLACK);

		DrawText("GOALPOSTS", (GoBallGo::screenWidth / 2) + 75, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) - 50, GoBallGo::titlesFontSize, DARKBLUE);
		DrawText("This are the obstacles that", (GoBallGo::screenWidth / 2) + 25, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4), GoBallGo::normalFontSize, BLACK);
		DrawText("you will have to dodge jumping", (GoBallGo::screenWidth / 2) + 15, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 30, GoBallGo::normalFontSize, BLACK);
		DrawText("through the walls.", (GoBallGo::screenWidth / 2) + 80, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 60, GoBallGo::normalFontSize, BLACK);
		DrawText("When you dodge between the", (GoBallGo::screenWidth / 2) + 25, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 90, GoBallGo::normalFontSize, BLACK);
		DrawText("walls you will get points", (GoBallGo::screenWidth / 2) + 50, (GoBallGo::screenHeight / 2) - (GoBallGo::screenHeight / 4) + 120, GoBallGo::normalFontSize, BLACK);

		DrawText("CONTROLS", (GoBallGo::screenWidth / 2) - (MeasureText("CONTROLS", GoBallGo::titlesFontSize) / 2), (GoBallGo::screenHeight / 2) + 25, GoBallGo::titlesFontSize, DARKBLUE);
		DrawText("Jump P1: SPACE / Jump P2: W / Pause: P", (GoBallGo::screenWidth / 2) - (MeasureText("Jump P1: SPACE / Jump P2: W / Pause: P", GoBallGo::titlesFontSize) / 2), (GoBallGo::screenHeight / 2) + 100, GoBallGo::titlesFontSize, BLACK);

		DrawRectangleLines((GoBallGo::screenWidth / 2) + (GoBallGo::screenWidth / 4) + 100, (GoBallGo::screenHeight / 8), 30, 100, BLACK);
		DrawRectangleLines((GoBallGo::screenWidth / 2) + (GoBallGo::screenWidth / 4) + 100, (GoBallGo::screenHeight / 8) + 150, 30, 100, BLACK);

		DrawLineEx(lineOneStartingPos, lineOneEndingPos, 10, BLACK);
		DrawLineEx(lineTwoStartingPos, lineTwoEndingPos, 10, BLACK);

		DrawTexture(exitButton.texture, static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), exitButton.buttonTint);

		DrawText("RETURN", static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (MeasureText("RETURN", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, exitButton.textColor);

		EndDrawing();
	}
}