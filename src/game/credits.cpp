#include "credits.h"

namespace GoBallGo
{
	void credits(SCREENS& currentScreen)
	{
		//Inits
		Button exitButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 10), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		
		exitButton.x -= exitButton.w / 2.0f;

		Vector2 mouse = { };

		while (!WindowShouldClose() && !exitButton.isPressed)
		{
			CreditsStructure::update(currentScreen, mouse, exitButton);

			CreditsStructure::draw(exitButton);
		}

		exitButton.isPressed = false;
	}
}

namespace CreditsStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& exitButton)
	{
		GoBallGo::mouseClick(mouse);
		mouseSelection(mouse, exitButton);

		if (exitButton.isPressed)
			currentScreen = MENU;
	}

	void draw(GoBallGo::Button exitButton)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("GAME DEVELOPERS", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("GAME DEVELOPERS", 40) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) - 150.0f), GoBallGo::titlesFontSize, YELLOW);
		DrawText("Juan Pablo 'Rushery' Pivetta", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("Juan Pablo 'Rushery' Pivetta", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) - 100.0f), GoBallGo::normalFontSize, WHITE);
		DrawText("Santiago Agustin 'Zomblack3' Britos", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) - 50.0f), GoBallGo::normalFontSize, WHITE);

		DrawText("ART", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("ART", 40) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) + 25.0f), GoBallGo::titlesFontSize, YELLOW);
		DrawText("Juan Pablo 'Rushery' Pivetta", static_cast<int>((GoBallGo::screenWidth / 2.0f) - (MeasureText("Juan Pablo 'Rushery' Pivetta", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) + 75.0f), GoBallGo::normalFontSize, WHITE);

		DrawRectangle(static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), static_cast<int>(exitButton.w), static_cast<int>(exitButton.h), SKYBLUE);
		DrawText("RETURN", static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (MeasureText("RETURN", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, WHITE);

		EndDrawing();
	}
}
