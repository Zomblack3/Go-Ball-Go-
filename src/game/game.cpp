#include "game.h"

#include "windowManagment.h"
#include "menu.h"
#include "gameplay.h"
#include "credits.h"

namespace run
{
	void game()
	{
		SCREENS currentScreen = MENU;

		bool isMenuMusicOn = true;
		bool isGameplayMusicOn = true;
		bool wasMusicOn = true;

		InitWindow(GoBallGo::screenWidth, GoBallGo::screenHeight, "Go Ball Go!!");

		InitAudioDevice();

		Sound music = LoadSound("res/audio/Mc_Caco_Boca_Yo_Te_Amo_Letra.wav");

		Font font = LoadFontEx("res/font/Jersey10_Regular.ttf", GoBallGo::normalFontSize, 0, 250);

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case MENU:

				GoBallGo::menu(currentScreen, music, isMenuMusicOn, wasMusicOn, font, isGameplayMusicOn);

				break;
			case GAMEPLAY:
				
				GoBallGo::gameplay(currentScreen, isMenuMusicOn, wasMusicOn, isGameplayMusicOn);
				
				break;
			case CREDITS:

				GoBallGo::credits(currentScreen, music, isMenuMusicOn);
				
				break;
			case EXIT:

				CloseWindow();

				break;
			default:
				break;
			}
		}

		UnloadSound(music);
		UnloadFont(font);

		CloseAudioDevice();
	}
}
