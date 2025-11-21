#include "game.h"

#include "windowManagment.h"
#include "menu.h"
#include "gameplay.h"
#include "credits.h"
#include "tutorial.h"

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

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case MENU:

				GoBallGo::menu(currentScreen, music, isMenuMusicOn, wasMusicOn, isGameplayMusicOn);

				break;
			case GAMEPLAY:
				
				GoBallGo::gameplay(currentScreen, isMenuMusicOn, wasMusicOn, isGameplayMusicOn);
				
				break;
			case CREDITS:

				GoBallGo::credits(currentScreen, music, isMenuMusicOn);
				
				break;
			case TUTORIAL:

				GoBallGo::tutorial(currentScreen, music, isMenuMusicOn);

				break;
			case EXIT:

				CloseWindow();

				break;
			default:
				break;
			}
		}

		UnloadSound(music);

		CloseAudioDevice();
	}
}
