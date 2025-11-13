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

		InitWindow(GoBallGo::screenWidth, GoBallGo::screenHeight, "Go! Ball Go!");

		InitAudioDevice();

		while (!WindowShouldClose())
		{
			switch (currentScreen)
			{
			case MENU:

				GoBallGo::menu(currentScreen);

				break;
			case GAMEPLAY:
				
				GoBallGo::gameplay(currentScreen);
				
				break;
			case CREDITS:

				GoBallGo::credits(currentScreen);
				
				break;
			case EXIT:

				CloseWindow();

				break;
			default:
				break;
			}
		}

		CloseAudioDevice();
	}
}
