#include "credits.h"

namespace GoBallGo
{
	void credits(SCREENS& currentScreen, Sound& music, bool isMusicOn)
	{
		Button exitButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 10), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		
		Texture2D background = LoadTexture("res/img/creditsBackground.png");
		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");

		Sound buttonsChangeStateSound = LoadSound("res/audio/button_sound.wav");

		exitButton.x -= exitButton.w / 2.0f;
		exitButton.texture = buttonsTexture;
		exitButton.changeStateSound = buttonsChangeStateSound;

		Vector2 mouse = { };

		while (!WindowShouldClose() && !exitButton.isPressed)
		{
			CreditsStructure::update(currentScreen, mouse, exitButton);

			CreditsStructure::draw(exitButton, background);

			playGameMusic(music, isMusicOn);
		}

		exitButton.isPressed = false;

		UnloadTexture(background);
		UnloadTexture(buttonsTexture);
		UnloadTexture(exitButton.texture);

		UnloadSound(buttonsChangeStateSound);
	}
}

namespace CreditsStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& exitButton)
	{
		mouse = GetMousePosition();

		mouseSelection(mouse, exitButton);

		if (exitButton.isPressed)
			currentScreen = MENU;
	}

	void draw(GoBallGo::Button exitButton, Texture2D background)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);

		DrawRectangle(static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) / 2.0f)) - 15, static_cast<int>((GoBallGo::screenHeight / 3.0f) - 150.0f) - 25, MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) + 25, 175, DARKBLUE);
		
		DrawText("GAME DEVELOPERS", static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("GAME DEVELOPERS", GoBallGo::titlesFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 3.0f) - 150.0f), GoBallGo::titlesFontSize, YELLOW);
		DrawText("Juan Pablo 'Rushery' Pivetta", static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("Juan Pablo 'Rushery' Pivetta", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 3.0f) - 100.0f), GoBallGo::normalFontSize, WHITE);
		DrawText("Santiago Agustin 'Zomblack3' Britos", static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 3.0f) - 50.0f), GoBallGo::normalFontSize, WHITE);

		DrawRectangle(static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) / 2.0f)) - 15, static_cast<int>((GoBallGo::screenHeight / 2.5f) - 150.0f) - 25, MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) + 25, 325, DARKBLUE);

		DrawText("ART", static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("ART", GoBallGo::titlesFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.5f) - 150.0f), GoBallGo::titlesFontSize, YELLOW);
		DrawText("Juan Pablo 'Rushery' Pivetta", static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("Juan Pablo 'Rushery' Pivetta", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.5f) - 100.0f), GoBallGo::normalFontSize, WHITE);
		DrawText("Santiago Agustin 'Zomblack3' Britos", static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("Santiago Agustin 'Zomblack3' Britos", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.5f) - 50.0f), GoBallGo::normalFontSize, WHITE);
		DrawText("Dmytro Aksonov (iStock)", static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("Dmytro Aksonov (iStock)", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.5f)), GoBallGo::normalFontSize, WHITE);
		DrawText("Kenney", static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("Kenney", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.5f) + 50.0f), GoBallGo::normalFontSize, WHITE);
		DrawText("Canva AI", static_cast<int>((GoBallGo::screenWidth - (GoBallGo::screenWidth / 4.0f)) - (MeasureText("Canva AI", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.5f) + 100.0f), GoBallGo::normalFontSize, WHITE);

		DrawRectangle(static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("El Cyber de Mc Caco", GoBallGo::titlesFontSize) / 2.0f)) - 15, static_cast<int>((GoBallGo::screenHeight / 2.0f)) - 25, MeasureText("El Cyber de Mc Caco", GoBallGo::titlesFontSize) + 25, 125, DARKBLUE);

		DrawText("SOUND", static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("SOUND", GoBallGo::titlesFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f)), GoBallGo::titlesFontSize, YELLOW);
		DrawText("El Cyber de Mc Caco", static_cast<int>((GoBallGo::screenWidth / 4.0f) - (MeasureText("El Cyber de Mc Caco", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>((GoBallGo::screenHeight / 2.0f) + 50.0f), GoBallGo::normalFontSize, WHITE);

		DrawTexture(exitButton.texture, static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), exitButton.buttonTint);

		DrawText("RETURN", static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (MeasureText("RETURN", GoBallGo::normalFontSize) / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, exitButton.textColor);

		EndDrawing();
	}
}
