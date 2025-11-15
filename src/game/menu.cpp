#include "menu.h"

#include <iostream>

namespace GoBallGo
{
	void menu(SCREENS& currentScreen, Sound& music, bool& isMusicOn, bool& wasMusicOn, Font font)
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

		playButton.x -= playButton.w / 2.0f;
		creditsButton.x -= creditsButton.w / 2.0f;
		exitButton.x -= exitButton.w / 2.0f;

		Vector2 mouse = { };

		while (!WindowShouldClose() && !playButton.isPressed && !creditsButton.isPressed && !exitButton.isPressed)
		{
			MenuStructure::update(currentScreen, mouse, playButton, creditsButton, exitButton, musicButton, buttonActivated, buttonDeactivated, isMusicOn, wasMusicOn);
			
			MenuStructure::draw(playButton, creditsButton, exitButton, musicButton, background, logo, font);
			
			playGameMusic(music, isMusicOn);
		}

		playButton.isPressed = false;
		creditsButton.isPressed = false;

		UnloadTexture(logo);
		UnloadTexture(buttonsTexture);
		UnloadTexture(buttonActivated);
		UnloadTexture(buttonDeactivated);
		UnloadTexture(playButton.texture);
		UnloadTexture(creditsButton.texture);
		UnloadTexture(exitButton.texture);
		UnloadTexture(musicButton.texture);
	}
}

namespace MenuStructure
{
	void update(SCREENS& currentScreen, Vector2& mouse, GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton, GoBallGo::Button& musicButton, Texture2D buttonOn, Texture2D buttonOff, bool& isMusicOn, bool& wasMusicOn)
	{
		mouse = GetMousePosition();

		GoBallGo::mouseSelection(mouse, playButton);
		GoBallGo::mouseSelection(mouse, creditsButton);
		GoBallGo::mouseSelection(mouse, exitButton);
		GoBallGo::mouseSelection(mouse, musicButton);

		if (playButton.isPressed)
		{
			currentScreen = GAMEPLAY;

			wasMusicOn = isMusicOn;

			isMusicOn = false;
		}

		if (creditsButton.isPressed)
			currentScreen = CREDITS;

		if (exitButton.isPressed)
			currentScreen = EXIT;

		if (musicButton.isPressed)
		{
			if (isMusicOn)
				isMusicOn = false;
			else
				isMusicOn = true;
		}

		if (isMusicOn)
			musicButton.texture = buttonOn;
		else
			musicButton.texture = buttonOff;
	}

	void draw(GoBallGo::Button& playButton, GoBallGo::Button& creditsButton, GoBallGo::Button& exitButton, GoBallGo::Button& musicButton, Texture2D background, Texture2D logo, Font font)
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

		DrawTextEx(font, "Music", { 50, (GoBallGo::screenHeight / 2.0f) + 5 }, 20, 2, YELLOW);

		DrawTextEx(font, buttonsTexts[0].c_str(), { (playButton.x + playButton.w / 2.0f) - (buttonsTextsLenghts[0] / 2.0f), playButton.y + GoBallGo::normalFontSize - 5 }, GoBallGo::normalFontSize, 2, playButton.textColor);
		DrawTextEx(font, buttonsTexts[1].c_str(), { (creditsButton.x + creditsButton.w / 2.0f) - (buttonsTextsLenghts[1] / 2.0f), creditsButton.y + GoBallGo::normalFontSize - 5 }, GoBallGo::normalFontSize, 2, creditsButton.textColor);
		DrawTextEx(font, buttonsTexts[2].c_str(), { (exitButton.x + exitButton.w / 2.0f) - (buttonsTextsLenghts[2] / 2.0f), exitButton.y + GoBallGo::normalFontSize - 5 }, GoBallGo::normalFontSize, 2, exitButton.textColor);

		DrawText("Ver: 0.5", versionTextX, versionTextY, GoBallGo::normalFontSize, WHITE);

		EndDrawing();
	}
}