#include "menu.h"

#include <iostream>

namespace GoBallGo
{
	void menu(SCREENS& currentScreen)
	{		
		Button playButton = initButton(screenWidth / 2.0f, screenHeight / 6.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button creditsButton = initButton(screenWidth / 2.0f, screenHeight / 2.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button exitButton = initButton(screenWidth / 2.0f, screenHeight / 3.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		
		playButton.x -= playButton.w / 2.0f;
		creditsButton.x -= creditsButton.w / 2.0f;
		exitButton.x -= exitButton.w / 2.0f;

		Vector2 mouse = { };

		while (!WindowShouldClose() && !playButton.isPressed && !creditsButton.isPressed && !exitButton.isPressed)
		{
			MenuStructure::update(currentScreen, mouse, playButton, creditsButton, exitButton);
			MenuStructure::draw(playButton, creditsButton, exitButton);
		}
		
		playButton.isPressed = false;
		creditsButton.isPressed = false;
	}
}

namespace MenuStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton)
	{
		GoBallGo::mouseClick(mouse);

		mouseSelection(mouse, playButton);
		mouseSelection(mouse, creditsButton);
		mouseSelection(mouse, exitButton);

		if (playButton.isPressed)
			currentScreen = GAMEPLAY;

		if (creditsButton.isPressed)
			currentScreen = CREDITS;

		if (exitButton.isPressed)
			currentScreen = EXIT;
	}

	void draw(GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton)
	{
		const int buttonsAmount = 3;
		const int versionTextX = GoBallGo::screenWidth - 65;
		const int versionTextY = GoBallGo::screenHeight - 15;

		std::string buttonsTexts[buttonsAmount] = { "START", "CREDITS", "EXIT" };

		int buttonsTextsLenghts[buttonsAmount] = { };

		for (int i = 0; i < buttonsAmount; i++)
			buttonsTextsLenghts[i] = MeasureText(buttonsTexts[i].c_str(), GoBallGo::normalFontSize);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangle(static_cast<int>(playButton.x), static_cast<int>(playButton.y), static_cast<int>(playButton.w), static_cast<int>(playButton.h), GREEN);
		DrawRectangle(static_cast<int>(creditsButton.x), static_cast<int>(creditsButton.y), static_cast<int>(creditsButton.w), static_cast<int>(creditsButton.h), YELLOW);
		DrawRectangle(static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), static_cast<int>(exitButton.w), static_cast<int>(exitButton.h), RED);

		DrawText(buttonsTexts[0].c_str(), static_cast<int>((playButton.x + playButton.w / 2.0f) - (buttonsTextsLenghts[0] / 2.0f)), static_cast<int>(playButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, BLACK);
		DrawText(buttonsTexts[1].c_str(), static_cast<int>((creditsButton.x + creditsButton.w / 2.0f) - (buttonsTextsLenghts[1] / 2.0f)), static_cast<int>(creditsButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, BLACK);
		DrawText(buttonsTexts[2].c_str(), static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (buttonsTextsLenghts[2] / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, BLACK);

		DrawText("Ver: 0.3", versionTextX, versionTextY, GoBallGo::normalFontSize, WHITE);

		EndDrawing();
	}
}