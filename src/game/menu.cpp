#include "menu.h"

#include <iostream>

namespace GoBallGo
{
	void menu(SCREENS& currentScreen)
	{
		Button playButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 1.5f), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button creditsButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 2.0f), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button exitButton = initButton(screenWidth / 2.0f, screenHeight - (screenHeight / 3.0f), BUTTONS_WIDTH, BUTTONS_HEIGHT, false);
		Button musicButton = initButton(10, screenHeight / 2.0f, 32.0f, 32.0f, false);

		Texture2D background = LoadTexture("res/img/menuBackground.png");
		Texture2D logo = LoadTexture("res/img/logo.png");

		Texture2D buttonsTexture = LoadTexture("res/img/button_rectangle_depth_gloss.png");
		Texture2D buttonActivated = LoadTexture("res/img/check_square_grey_checkmark.png");
		Texture2D buttonDeactivated = LoadTexture("res/img/check_square_grey_cross.png");

		playButton.texture = buttonsTexture;
		creditsButton.texture = buttonsTexture;
		exitButton.texture = buttonsTexture;
		musicButton.texture = buttonActivated;

		Sound music = LoadSound("res/audio/Mc_Caco_Boca_Yo_Te_Amo_Letra.wav");

		playButton.x -= playButton.w / 2.0f;
		creditsButton.x -= creditsButton.w / 2.0f;
		exitButton.x -= exitButton.w / 2.0f;

		Vector2 mouse = { };

		while (!WindowShouldClose() && !playButton.isPressed && !creditsButton.isPressed && !exitButton.isPressed)
		{
			MenuStructure::update(currentScreen, mouse, playButton, creditsButton, exitButton, musicButton, buttonActivated, buttonDeactivated);
			MenuStructure::draw(playButton, creditsButton, exitButton, musicButton, background, logo);
			MenuStructure::playMenuSounds(music);
		}

		playButton.isPressed = false;
		creditsButton.isPressed = false;

		UnloadSound(music);
		UnloadTexture(logo);
		UnloadTexture(buttonsTexture);
		UnloadTexture(playButton.texture);
		UnloadTexture(creditsButton.texture);
		UnloadTexture(exitButton.texture);
	}
}

namespace MenuStructure
{
	bool isMusicOn = true;

	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton, GoBallGo::Button& musicButton, Texture2D buttonOn, Texture2D buttonOff)
	{
		mouse = GetMousePosition();

		GoBallGo::mouseSelection(mouse, playButton);
		GoBallGo::mouseSelection(mouse, creditsButton);
		GoBallGo::mouseSelection(mouse, exitButton);
		GoBallGo::mouseSelection(mouse, musicButton);

		if (playButton.isPressed)
			currentScreen = GAMEPLAY;

		if (creditsButton.isPressed)
			currentScreen = CREDITS;

		if (exitButton.isPressed)
			currentScreen = EXIT;

		if (musicButton.isPressed)
		{
			if (isMusicOn)
			{
				isMusicOn = false;
				musicButton.texture = buttonOff;
			}
			else
			{
				isMusicOn = true;
				musicButton.texture = buttonOn;
			}
		}
	}

	void draw(GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton, GoBallGo::Button& musicButton, Texture2D background, Texture2D logo)
	{
		const int buttonsAmount = 3;
		const int versionTextX = 10;
		const int versionTextY = GoBallGo::screenHeight - 30;

		std::string buttonsTexts[buttonsAmount] = { "START", "CREDITS", "EXIT" };

		int buttonsTextsLenghts[buttonsAmount] = { };

		for (int i = 0; i < buttonsAmount; i++)
			buttonsTextsLenghts[i] = MeasureText(buttonsTexts[i].c_str(), GoBallGo::normalFontSize);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);
		DrawTexture(logo, (GoBallGo::screenWidth / 2) - (logo.width / 2), 50, WHITE);

		DrawTexture(musicButton.texture, static_cast<int>(musicButton.x), static_cast<int>(musicButton.y), musicButton.buttonTint);

		DrawTexture(playButton.texture, static_cast<int>(playButton.x), static_cast<int>(playButton.y), playButton.buttonTint);
		DrawTexture(creditsButton.texture, static_cast<int>(creditsButton.x), static_cast<int>(creditsButton.y), creditsButton.buttonTint);
		DrawTexture(exitButton.texture, static_cast<int>(exitButton.x), static_cast<int>(exitButton.y), exitButton.buttonTint);

		DrawText("Music", 50, static_cast<int>((GoBallGo::screenHeight / 2.0f) + 5), 20, YELLOW);

		DrawText(buttonsTexts[0].c_str(), static_cast<int>((playButton.x + playButton.w / 2.0f) - (buttonsTextsLenghts[0] / 2.0f)), static_cast<int>(playButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, playButton.textColor);
		DrawText(buttonsTexts[1].c_str(), static_cast<int>((creditsButton.x + creditsButton.w / 2.0f) - (buttonsTextsLenghts[1] / 2.0f)), static_cast<int>(creditsButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, creditsButton.textColor);
		DrawText(buttonsTexts[2].c_str(), static_cast<int>((exitButton.x + exitButton.w / 2.0f) - (buttonsTextsLenghts[2] / 2.0f)), static_cast<int>(exitButton.y + GoBallGo::normalFontSize - 5), GoBallGo::normalFontSize, exitButton.textColor);

		DrawText("Ver: 0.5", versionTextX, versionTextY, GoBallGo::normalFontSize, WHITE);

		EndDrawing();
	}

	void playMenuSounds(Sound& music)
	{
		if (!IsSoundPlaying(music))
			PlaySound(music);

		if (!isMusicOn)
			PauseSound(music);
		else
			ResumeSound(music);
	}
}