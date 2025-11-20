#pragma once

#include "raylib.h"

#include "objects/buttons.h"

enum SCREENS
{
	MENU,
	GAMEPLAY,
	CREDITS,
	TUTORIAL,
	EXIT
};

namespace GoBallGo
{
	void mouseSelection(Vector2 mousePos, Button& button);
	void playGameMusic(Sound& music, bool isMusicOn);

	bool isMouseInButton(Vector2 mousePos, Button button);

	const int screenWidth = 1024;
	const int screenHeight = 768;

	const int titlesFontSize = 30;
	const int normalFontSize = 20;
}